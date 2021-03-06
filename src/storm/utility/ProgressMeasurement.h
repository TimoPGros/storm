#pragma once

#include <chrono>
#include <ostream>
#include <boost/optional.hpp>

namespace storm {
    namespace utility {

        /*!
         * A class that provides convenience operations to display run times.
         */
        class ProgressMeasurement {
        public:
            typedef decltype(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::seconds::zero()).count()) SecondType;
            typedef decltype(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::milliseconds::zero()).count()) MilisecondType;
            typedef decltype(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::nanoseconds::zero()).count()) NanosecondType;
            
            /*!
             * Initializes progress measurement.
             * @param itemName the name of what we are counting (iterations, states, ...).
             */
            ProgressMeasurement(std::string const& itemName = "items");
            
            /*!
             * Starts a new measurement, dropping all progress information collected so far.
             * @param startCount the initial count.
             */
            void startNewMeasurement(uint64_t startCount);
            
            /*!
             * Updates the progress to the current count.
             * @param count The currently achieved count.
             * @return true iff the progress was printed (i.e., the delay passed).
             */
            bool updateProgress(uint64_t count);
            
            /*!
             * Updates the progress to the current count.
             * @param count The currently achieved count.
             * @param outstream The stream to which the progress is printed (if the delay passed)
             * @return true iff the progress was printed (i.e., the delay passed)
             */
            bool updateProgress(uint64_t value, std::ostream& outstream);
            
            /*!
             * Returns whether a maximal count (which is required to achieve 100% progress) has been specified
             */
            bool isMaxCountSet() const;
            
            /*!
             * Returns the maximal possible count (if specified).
             */
            uint64_t getMaxCount() const;
            
            /*!
             * Sets the maximal possible count.
             */
            void setMaxCount(uint64_t maxCount);
            
            /*!
             * Erases a previously specified maximal count.
             */
            void unsetMaxCount();
            
            /*!
             * Returns the currently specified minimal delay (in seconds) between two progress messages.
             */
            uint64_t getShowProgressDelay() const;
            
            /*!
             * Customizes the minimal delay between two progress messages.
             * @param delay the delay (in seconds).
             */
            void setShowProgressDelay(uint64_t delay);
            
            /*!
             * Returns the current name of what we are counting (e.g. iterations, states, ...)
             */
            std::string const& getItemName() const;
            
            /*!
             * Customizes the name of what we are counting (e.g. iterations, states, ...)
             * @param name the name of what we are counting.
             */
            void setItemName(std::string const& name);

        private:
        
            // The delay (in seconds) between progress emission.
            uint64_t delay;
            // A name for what this is measuring (iterations, states, ...)
            std::string itemName;
            
            // The maximal count that can be achieved. Zero means unspecified.
            uint64_t maxCount;
            
            // The last displayed count
            uint64_t lastDisplayedCount;
            
            std::chrono::high_resolution_clock::time_point timeOfStart;
            std::chrono::high_resolution_clock::time_point timeOfLastMessage;
            
        };
        
    }
}
