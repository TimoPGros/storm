#ifndef STORM_SOLVER_Z3SMTSOLVER
#define STORM_SOLVER_Z3SMTSOLVER

#include "storm-config.h"
#include "src/solver/SmtSolver.h"
#include "src/adapters/Z3ExpressionAdapter.h"

#include "z3++.h"
#include "z3.h"

namespace storm {
	namespace solver {
		class Z3SmtSolver : public SmtSolver {
		public:
			Z3SmtSolver(Options options = Options::ModelGeneration);
			virtual ~Z3SmtSolver();

			virtual void push() override;

			virtual void pop() override;

			virtual void pop(uint_fast64_t n) override;

			virtual void reset() override;

			virtual void assertExpression(storm::expressions::Expression const& e) override;

			virtual CheckResult check() override;

			virtual CheckResult checkWithAssumptions(std::set<storm::expressions::Expression> const& assumptions) override;

			virtual CheckResult checkWithAssumptions(std::initializer_list<storm::expressions::Expression> assumptions) override;

			virtual storm::expressions::SimpleValuation getModel() override;

			virtual std::vector<storm::expressions::SimpleValuation> allSat(std::vector<storm::expressions::Expression> const& important) override;

			virtual uint_fast64_t allSat(std::vector<storm::expressions::Expression> const& important, std::function<bool(storm::expressions::SimpleValuation&)> callback) override;

			virtual std::vector<storm::expressions::Expression> getUnsatAssumptions() override;

		protected:
			virtual storm::expressions::SimpleValuation z3ModelToStorm(z3::model m);
		private:

#ifdef STORM_HAVE_Z3
			z3::context m_context;
			z3::solver m_solver;
			storm::adapters::Z3ExpressionAdapter m_adapter;

			bool lastCheckAssumptions;
			CheckResult lastResult;
#endif
		};
	}
}
#endif // STORM_SOLVER_Z3SMTSOLVER