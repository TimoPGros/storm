#ifndef STORM_STORAGE_DD_CUDDDD_H_
#define STORM_STORAGE_DD_CUDDDD_H_

#include <unordered_map>
#include <set>
#include <memory>

#include "src/storage/dd/Dd.h"
#include "utility\OsDetection.h"

// Include the C++-interface of CUDD.
#include "cuddObj.hh"

namespace storm {
    namespace dd {
        // Forward-declare the DdManager class.
        template<DdType Type> class DdManager;
        
        template<>
        class Dd<CUDD> {
        public:
            // Declare the DdManager class as friend so it can access the internals of a DD.
            friend class DdManager<CUDD>;
            
            // Instantiate all copy/move constructors/assignments with the default implementation.
            Dd() = default;
            Dd(Dd<CUDD> const& other) = default;
			Dd& operator=(Dd<CUDD> const& other) = default;
			#ifndef WINDOWS
				Dd(Dd<CUDD>&& other) = default;
				Dd& operator=(Dd<CUDD>&& other) = default;
			#endif
            
            /*!
             * Retrieves whether the two DDs represent the same function.
             *
             * @param other The DD that is to be compared with the current one.
             */
            bool operator==(Dd<CUDD> const& other) const;
            
            /*!
             * Adds the two DDs.
             *
             * @param other The DD to add to the current one.
             * @return The result of the addition.
             */
            Dd<CUDD> operator+(Dd<CUDD> const& other) const;

            /*!
             * Adds the given DD to the current one.
             *
             * @param other The DD to add to the current one.
             * @return A reference to the current DD after the operation.
             */
            Dd<CUDD>& operator+=(Dd<CUDD> const& other);
            
            /*!
             * Multiplies the two DDs.
             *
             * @param other The DD to multiply with the current one.
             * @return The result of the multiplication.
             */
            Dd<CUDD> operator*(Dd<CUDD> const& other) const;

            /*!
             * Multiplies the given DD with the current one and assigns the result to the current DD.
             *
             * @param other The DD to multiply with the current one.
             * @return A reference to the current DD after the operation.
             */
            Dd<CUDD>& operator*=(Dd<CUDD> const& other);
            
            /*!
             * Subtracts the given DD from the current one.
             *
             * @param other The DD to subtract from the current one.
             * @return The result of the subtraction.
             */
            Dd<CUDD> operator-(Dd<CUDD> const& other) const;
            
            /*!
             * Subtracts the given DD from the current one and assigns the result to the current DD.
             *
             * @param other The DD to subtract from the current one.
             * @return A reference to the current DD after the operation.
             */
            Dd<CUDD>& operator-=(Dd<CUDD> const& other);
            
            /*!
             * Divides the current DD by the given one.
             *
             * @param other The DD by which to divide the current one.
             * @return The result of the division.
             */
            Dd<CUDD> operator/(Dd<CUDD> const& other) const;
            
            /*!
             * Divides the current DD by the given one and assigns the result to the current DD.
             *
             * @param other The DD by which to divide the current one.
             * @return A reference to the current DD after the operation.
             */
            Dd<CUDD>& operator/=(Dd<CUDD> const& other);
            
            /*!
             * Subtracts the DD from the constant zero function.
             *
             * @return The resulting function represented as a DD.
             */
            Dd<CUDD> minus() const;
            
            /*!
             * Retrieves the logical complement of the current DD. The result will map all encodings with a value
             * unequal to zero to false and all others to true.
             *
             * @return The logical complement of the current DD.
             */
            Dd<CUDD> operator~() const;
            
            /*!
             * Logically complements the current DD. The result will map all encodings with a value
             * unequal to zero to false and all others to true.
             *
             * @return A reference to the current DD after the operation.
             */
            Dd<CUDD>& complement();
            
            /*!
             * Retrieves the function that maps all evaluations to one that have an identical function values.
             *
             * @param other The DD with which to perform the operation.
             * @return The resulting function represented as a DD.
             */
            Dd<CUDD> equals(Dd<CUDD> const& other) const;
            
            /*!
             * Retrieves the function that maps all evaluations to one that have distinct function values.
             *
             * @param other The DD with which to perform the operation.
             * @return The resulting function represented as a DD.
             */
            Dd<CUDD> notEquals(Dd<CUDD> const& other) const;
            
            /*!
             * Retrieves the function that maps all evaluations to one whose function value in the first DD are less
             * than the one in the given DD.
             *
             * @param other The DD with which to perform the operation.
             * @return The resulting function represented as a DD.
             */
            Dd<CUDD> less(Dd<CUDD> const& other) const;
            
            /*!
             * Retrieves the function that maps all evaluations to one whose function value in the first DD are less or
             * equal than the one in the given DD.
             *
             * @param other The DD with which to perform the operation.
             * @return The resulting function represented as a DD.
             */
            Dd<CUDD> lessOrEqual(Dd<CUDD> const& other) const;
            
            /*!
             * Retrieves the function that maps all evaluations to one whose function value in the first DD are greater
             * than the one in the given DD.
             *
             * @param other The DD with which to perform the operation.
             * @return The resulting function represented as a DD.
             */
            Dd<CUDD> greater(Dd<CUDD> const& other) const;
            
            /*!
             * Retrieves the function that maps all evaluations to one whose function value in the first DD are greater
             * or equal than the one in the given DD.
             *
             * @param other The DD with which to perform the operation.
             * @return The resulting function represented as a DD.
             */
            Dd<CUDD> greaterOrEqual(Dd<CUDD> const& other) const;
            
            /*!
             * Existentially abstracts from the given meta variables.
             *
             * @param metaVariableNames The names of all meta variables from which to abstract.
             */
            void existsAbstract(std::set<std::string> const& metaVariableNames);

            /*!
             * Sum-abstracts from the given meta variables.
             *
             * @param metaVariableNames The names of all meta variables from which to abstract.
             */
            void sumAbstract(std::set<std::string> const& metaVariableNames);
            
            /*!
             * Min-abstracts from the given meta variables.
             *
             * @param metaVariableNames The names of all meta variables from which to abstract.
             */
            void minAbstract(std::set<std::string> const& metaVariableNames);
            
            /*!
             * Max-abstracts from the given meta variables.
             *
             * @param metaVariableNames The names of all meta variables from which to abstract.
             */
            void maxAbstract(std::set<std::string> const& metaVariableNames);

            /*!
             * Swaps the given pairs of meta variables in the DD. The pairs of meta variables must be guaranteed to have
             * the same number of underlying DD variables.
             *
             * @param metaVariablePairs A vector of meta variable pairs that are to be swapped for one another.
             */
            void swapVariables(std::vector<std::pair<std::string, std::string>> const& metaVariablePairs);
            
            /*!
             * Multiplies the current DD (representing a matrix) with the given matrix by summing over the given meta
             * variables.
             *
             * @param otherMatrix The matrix with which to multiply.
             * @param summationMetaVariableNames The names of the meta variables over which to sum during the matrix-
             * matrix multiplication.
             * @return A DD representing the result of the matrix-matrix multiplication.
             */
            Dd<CUDD> multiplyMatrix(Dd<CUDD> const& otherMatrix, std::set<std::string> const& summationMetaVariableNames);
            
            /*!
             * Retrieves the number of encodings that are mapped to a non-zero value.
             *
             * @return The number of encodings that are mapped to a non-zero value.
             */
            uint_fast64_t getNonZeroCount() const;
            
            /*!
             * Retrieves the number of leaves of the DD.
             *
             * @return The number of leaves of the DD.
             */
            uint_fast64_t getLeafCount() const;
            
            /*!
             * Retrieves the number of nodes necessary to represent the DD.
             *
             * @return The number of nodes in this DD.
             */
            uint_fast64_t getNodeCount() const;
            
            /*!
             * Retrieves the lowest function value of any encoding.
             *
             * @return The lowest function value of any encoding.
             */
            double getMin() const;
            
            /*!
             * Retrieves the highest function value of any encoding.
             *
             * @return The highest function value of any encoding.
             */
            double getMax() const;
            
            /*!
             * Sets the function values of all encodings that have the given value of the meta variable to the given
             * target value.
             *
             * @param metaVariableName The name of the meta variable that has to be equal to the given value.
             * @param variableValue The value that the meta variable is supposed to have. This must be within the range
             * of the meta variable.
             * @param targetValue The new function value of the modified encodings.
             */
            void setValue(std::string const& metaVariableName, int_fast64_t variableValue, double targetValue);

            /*!
             * Sets the function values of all encodings that have the given values of the two meta variables to the
             * given target value.
             *
             * @param metaVariableName1 The name of the first meta variable that has to be equal to the first given
             * value.
             * @param variableValue1 The value that the first meta variable is supposed to have. This must be within the
             * range of the meta variable.
             * @param metaVariableName2 The name of the first meta variable that has to be equal to the second given
             * value.
             * @param variableValue2 The value that the second meta variable is supposed to have. This must be within
             * the range of the meta variable.
             * @param targetValue The new function value of the modified encodings.
             */
            void setValue(std::string const& metaVariableName1, int_fast64_t variableValue1, std::string const& metaVariableName2, int_fast64_t variableValue2, double targetValue);
            
            /*!
             * Sets the function values of all encodings that have the given values of the given meta variables to the
             * given target value.
             *
             * @param metaVariableNameToValueMap A mapping of meta variable names to the values they are supposed to
             * have. All values must be within the range of the respective meta variable.
             * @param targetValue The new function value of the modified encodings.
             */
            void setValue(std::unordered_map<std::string, int_fast64_t> const& metaVariableNameToValueMap, double targetValue);
            
            /*!
             * Retrieves whether this DD represents the constant one function.
             *
             * @return True if this DD represents the constant one function.
             */
            bool isOne() const;
            
            /*!
             * Retrieves whether this DD represents the constant zero function.
             *
             * @return True if this DD represents the constant zero function.
             */
            bool isZero() const;
            
            /*!
             * Retrieves whether the given meta variable is contained in the DD.
             *
             * @param metaVariableName The name of the meta variable for which to query membership.
             * @return True iff the meta variable is contained in the DD.
             */
            bool containsMetaVariable(std::string const& metaVariableName) const;
            
            /*!
             * Retrieves whether the given meta variables are all contained in the DD.
             *
             * @param metaVariableNames The names of the meta variable for which to query membership.
             * @return True iff all meta variables are contained in the DD.
             */
            bool containsMetaVariables(std::set<std::string> metaVariableNames) const;
            
            /*!
             * Retrieves the set of all names of meta variables contained in the DD.
             *
             * @return The set of names of all meta variables contained in the DD.
             */
            std::set<std::string> const& getContainedMetaVariableNames() const;
            
            /*!
             * Retrieves the set of all names of meta variables contained in the DD.
             *
             * @return The set of names of all meta variables contained in the DD.
             */
            std::set<std::string>& getContainedMetaVariableNames();
            
            /*!
             * Exports the DD to the given file in the dot format.
             *
             * @param filename The name of the file to which the DD is to be exported.
             */
            void exportToDot(std::string const& filename) const;
            
            /*!
             * Retrieves the manager that is responsible for this DD.
             *
             * A pointer to the manager that is responsible for this DD.
             */
            std::shared_ptr<DdManager<CUDD>> getDdManager() const;
            
        private:
            /*!
             * Retrieves the CUDD ADD object associated with this DD.
             *
             * @return The CUDD ADD object assoicated with this DD.
             */
            ADD getCuddAdd();
            
            /*!
             * Retrieves the CUDD ADD object associated with this DD.
             *
             * @return The CUDD ADD object assoicated with this DD.
             */
            ADD const& getCuddAdd() const;
            
            /*!
             * Adds the given meta variable name to the set of meta variables that are contained in this DD.
             *
             * @param metaVariableName The name of the meta variable to add.
             */
            void addContainedMetaVariable(std::string const& metaVariableName);
            
            /*!
             * Removes the given meta variable name to the set of meta variables that are contained in this DD.
             *
             * @param metaVariableName The name of the meta variable to remove.
             */
            void removeContainedMetaVariable(std::string const& metaVariableName);

            /*!
             * Creates a DD that encapsulates the given CUDD ADD.
             *
             * @param ddManager The manager responsible for this DD.
             * @param cuddAdd The CUDD ADD to store.
             * @param
             */
            Dd(std::shared_ptr<DdManager<CUDD>> ddManager, ADD cuddAdd, std::set<std::string> const& containedMetaVariableNames);
            
            // A pointer to the manager responsible for this DD.
            std::shared_ptr<DdManager<CUDD>> ddManager;

            // The ADD created by CUDD.
            ADD cuddAdd;
            
            // The names of all meta variables that appear in this DD.
            std::set<std::string> containedMetaVariableNames;
        };
    }
}

#endif /* STORM_STORAGE_DD_CUDDDD_H_ */