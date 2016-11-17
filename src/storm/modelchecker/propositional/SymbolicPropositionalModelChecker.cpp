#include "src/modelchecker/propositional/SymbolicPropositionalModelChecker.h"

#include "src/storage/dd/Add.h"
#include "src/storage/dd/DdManager.h"

#include "src/models/symbolic/Dtmc.h"
#include "src/models/symbolic/Ctmc.h"
#include "src/models/symbolic/Mdp.h"
#include "src/models/symbolic/StandardRewardModel.h"

#include "src/modelchecker/results/SymbolicQualitativeCheckResult.h"

#include "src/logic/FragmentSpecification.h"

#include "src/utility/macros.h"
#include "src/exceptions/InvalidPropertyException.h"

namespace storm {
    namespace modelchecker {
        template<typename ModelType>
        SymbolicPropositionalModelChecker<ModelType>::SymbolicPropositionalModelChecker(ModelType const& model) : model(model) {
            // Intentionally left empty.
        }
        
        template<typename ModelType>
        bool SymbolicPropositionalModelChecker<ModelType>::canHandle(CheckTask<storm::logic::Formula, ValueType> const& checkTask) const {
            storm::logic::Formula const& formula = checkTask.getFormula();
            return formula.isInFragment(storm::logic::propositional());
        }
        
        template<typename ModelType>
        std::unique_ptr<CheckResult> SymbolicPropositionalModelChecker<ModelType>::checkBooleanLiteralFormula(CheckTask<storm::logic::BooleanLiteralFormula, ValueType> const& checkTask) {
            storm::logic::BooleanLiteralFormula const& stateFormula = checkTask.getFormula();
            if (stateFormula.isTrueFormula()) {
                return std::unique_ptr<CheckResult>(new SymbolicQualitativeCheckResult<DdType>(model.getReachableStates(), model.getReachableStates()));
            } else {
                return std::unique_ptr<CheckResult>(new SymbolicQualitativeCheckResult<DdType>(model.getReachableStates(), model.getManager().getBddZero()));
            }
        }
        
        template<typename ModelType>
        std::unique_ptr<CheckResult> SymbolicPropositionalModelChecker<ModelType>::checkAtomicLabelFormula(CheckTask<storm::logic::AtomicLabelFormula, ValueType> const& checkTask) {
            storm::logic::AtomicLabelFormula const& stateFormula = checkTask.getFormula();
            STORM_LOG_THROW(model.hasLabel(stateFormula.getLabel()), storm::exceptions::InvalidPropertyException, "The property refers to unknown label '" << stateFormula.getLabel() << "'.");
            return std::unique_ptr<CheckResult>(new SymbolicQualitativeCheckResult<DdType>(model.getReachableStates(), model.getStates(stateFormula.getLabel())));
        }
        
        template<typename ModelType>
        std::unique_ptr<CheckResult> SymbolicPropositionalModelChecker<ModelType>::checkAtomicExpressionFormula(CheckTask<storm::logic::AtomicExpressionFormula, ValueType> const& checkTask) {
            storm::logic::AtomicExpressionFormula const& stateFormula = checkTask.getFormula();
            return std::unique_ptr<CheckResult>(new SymbolicQualitativeCheckResult<DdType>(model.getReachableStates(), model.getStates(stateFormula.getExpression())));
        }
        
        template<typename ModelType>
        ModelType const& SymbolicPropositionalModelChecker<ModelType>::getModel() const {
            return model;
        }

        
        // Explicitly instantiate the template class.


        template class SymbolicPropositionalModelChecker<storm::models::symbolic::Dtmc<storm::dd::DdType::CUDD, double>>;
        template class SymbolicPropositionalModelChecker<storm::models::symbolic::Ctmc<storm::dd::DdType::CUDD, double>>;
        template class SymbolicPropositionalModelChecker<storm::models::symbolic::Mdp<storm::dd::DdType::CUDD, double>>;
        template class SymbolicPropositionalModelChecker<storm::models::symbolic::Dtmc<storm::dd::DdType::Sylvan, double>>;
        template class SymbolicPropositionalModelChecker<storm::models::symbolic::Ctmc<storm::dd::DdType::Sylvan, double>>;
        template class SymbolicPropositionalModelChecker<storm::models::symbolic::Mdp<storm::dd::DdType::Sylvan, double>>;

    }
}