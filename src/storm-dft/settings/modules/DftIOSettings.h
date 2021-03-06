#pragma once

#include "storm/settings/modules/ModuleSettings.h"

namespace storm {
    namespace settings {
        namespace modules {

            /*!
             * This class represents the settings for IO operations concerning DFTs.
             */
            class DftIOSettings : public ModuleSettings {
            public:

                /*!
                 * Creates a new set of IO settings for DFTs.
                 */
                DftIOSettings();
                
                /*!
                 * Retrieves whether the dft file option was set.
                 *
                 * @return True if the dft file option was set.
                 */
                bool isDftFileSet() const;
                
                /*!
                 * Retrieves the name of the file that contains the dft specification.
                 *
                 * @return The name of the file that contains the dft specification.
                 */
                std::string getDftFilename() const;

                /*!
                 * Retrieves whether the dft file option for Json was set.
                 *
                 * @return True if the dft file option was set.
                 */
                bool isDftJsonFileSet() const;

                /*!
                 * Retrieves the name of the json file that contains the dft specification.
                 *
                 * @return The name of the json file that contains the dft specification.
                 */
                std::string getDftJsonFilename() const;

                /*!
                 * Retrieves whether the property expected time should be used.
                 *
                 * @return True iff the option was set.
                 */
                bool usePropExpectedTime() const;
                
                /*!
                 * Retrieves whether the property probability should be used.
                 *
                 * @return True iff the option was set.
                 */
                bool usePropProbability() const;
                
                /*!
                 * Retrieves whether the property timebound should be used.
                 *
                 * @return True iff the option was set.
                 */
                bool usePropTimebound() const;

                /*!
                 * Retrieves the timebound for the timebound property.
                 *
                 * @return The timebound.
                 */
                double getPropTimebound() const;

                /*!
                 * Retrieves whether the property timepoints should be used.
                 *
                 * @return True iff the option was set.
                 */
                bool usePropTimepoints() const;

                /*!
                 * Retrieves the settings for the timepoints property.
                 *
                 * @return The timepoints.
                 */
                std::vector<double> getPropTimepoints() const;

                /*!
                 * Retrieves whether the minimal value should be computed for non-determinism.
                 *
                 * @return True iff the option was set.
                 */
                bool isComputeMinimalValue() const;

                /*!
                 * Retrieves whether the maximal value should be computed for non-determinism.
                 *
                 * @return True iff the option was set.
                 */
                bool isComputeMaximalValue() const;

                /*!
                 * Retrieves whether the DFT should be transformed into a GSPN.
                 *
                 * @return True iff the option was set.
                 */
                bool isTransformToGspn() const;

                /*!
                 * Retrieves whether the export to Json file option was set.
                 *
                 * @return True if the export to json file option was set.
                 */
                bool isExportToJson() const;

                /*!
                 * Retrieves the name of the json file to export to.
                 *
                 * @return The name of the json file to export to.
                 */
                std::string getExportJsonFilename() const;
                
                bool check() const override;
                void finalize() override;

                // The name of the module.
                static const std::string moduleName;

            private:
               // Define the string names of the options as constants.
                static const std::string dftFileOptionName;
                static const std::string dftFileOptionShortName;
                static const std::string dftJsonFileOptionName;
                static const std::string dftJsonFileOptionShortName;
                static const std::string propExpectedTimeOptionName;
                static const std::string propExpectedTimeOptionShortName;
                static const std::string propProbabilityOptionName;
                static const std::string propTimeboundOptionName;
                static const std::string propTimepointsOptionName;
                static const std::string minValueOptionName;
                static const std::string maxValueOptionName;
                static const std::string transformToGspnOptionName;
                static const std::string exportToJsonOptionName;
                
            };

        } // namespace modules
    } // namespace settings
} // namespace storm
