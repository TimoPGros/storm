#pragma once

#include <memory>

#include "storm/storage/dd/DdType.h"

#include "storm/models/symbolic/Model.h"
#include "storm/models/sparse/Model.h"

#include "storm/storage/dd/bisimulation/Partition.h"
#include "storm/storage/dd/bisimulation/PreservationInformation.h"

#include "storm/settings/modules/BisimulationSettings.h"

namespace storm {
    namespace dd {
        namespace bisimulation {
            
            template<storm::dd::DdType DdType, typename ValueType>
            class PartialQuotientExtractor {
            public:
                PartialQuotientExtractor(storm::models::symbolic::Model<DdType, ValueType> const& model);
                
                std::shared_ptr<storm::models::Model<ValueType>> extract(Partition<DdType, ValueType> const& partition, PreservationInformation<DdType, ValueType> const& preservationInformation);
                
            private:
                std::shared_ptr<storm::models::symbolic::Model<DdType, ValueType>> extractDdQuotient(Partition<DdType, ValueType> const& partition, PreservationInformation<DdType, ValueType> const& preservationInformation);
                
                // The model for which to compute the partial quotient.
                storm::models::symbolic::Model<DdType, ValueType> const& model;
                
                storm::settings::modules::BisimulationSettings::QuotientFormat quotientFormat;
            };
            
        }
    }
}
