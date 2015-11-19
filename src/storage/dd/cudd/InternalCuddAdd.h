#ifndef STORM_STORAGE_DD_CUDD_INTERNALCUDDADD_H_
#define STORM_STORAGE_DD_CUDD_INTERNALCUDDADD_H_

#include <set>

#include "src/storage/dd/DdType.h"
#include "src/storage/dd/InternalAdd.h"

#include "src/storage/expressions/Variable.h"

// Include the C++-interface of CUDD.
#include "cuddObj.hh"

namespace storm {
    namespace storage {
        template<typename T>
        class SparseMatrix;
        
        class BitVector;
        
        template<typename E, typename V>
        class MatrixEntry;
    }
    
    namespace dd {
        template<DdType LibraryType>
        class DdManager;

        template<DdType LibraryType>
        class InternalDdManager;
        
        template<DdType LibraryType>
        class InternalBdd;

        template<DdType LibraryType, typename ValueType>
        class AddIterator;
        
        template<DdType LibraryType>
        class Odd;
        
        template<typename ValueType>
        class InternalAdd<DdType::CUDD, ValueType> {
        public:
            friend class Odd<DdType::CUDD>;
            
            /*!
             * Creates an ADD that encapsulates the given CUDD ADD.
             *
             * @param ddManager The manager responsible for this DD.
             * @param cuddAdd The CUDD ADD to store.
             * @param containedMetaVariables The meta variables that appear in the DD.
             */
            InternalAdd(InternalDdManager<DdType::CUDD> const* ddManager, ADD cuddAdd);
            
            // Instantiate all copy/move constructors/assignments with the default implementation.
            InternalAdd() = default;
            InternalAdd(InternalAdd<DdType::CUDD, ValueType> const& other) = default;
            InternalAdd& operator=(InternalAdd<DdType::CUDD, ValueType> const& other) = default;
            InternalAdd(InternalAdd<DdType::CUDD, ValueType>&& other) = default;
            InternalAdd& operator=(InternalAdd<DdType::CUDD, ValueType>&& other) = default;
            
            /*!
             * Retrieves whether the two DDs represent the same function.
             *
             * @param other The DD that is to be compared with the current one.
             * @return True if the DDs represent the same function.
             */
            bool operator==(InternalAdd<DdType::CUDD, ValueType> const& other) const;
            
            /*!
             * Retrieves whether the two DDs represent different functions.
             *
             * @param other The DD that is to be compared with the current one.
             * @return True if the DDs represent the different functions.
             */
            bool operator!=(InternalAdd<DdType::CUDD, ValueType> const& other) const;
            
            /*!
             * Performs an if-then-else with the given operands, i.e. maps all valuations that are mapped to a non-zero
             * function value to the function values specified by the first DD and all others to the function values
             * specified by the second DD.
             *
             * @param thenDd The ADD specifying the 'then' part.
             * @param elseDd The ADD specifying the 'else' part.
             * @return The ADD corresponding to the if-then-else of the operands.
             */
            InternalAdd<DdType::CUDD, ValueType> ite(InternalAdd<DdType::CUDD, ValueType> const& thenAdd, InternalAdd<DdType::CUDD, ValueType> const& elseAdd) const;
            
            /*!
             * Logically inverts the current ADD. That is, all inputs yielding non-zero values will be mapped to zero in
             * the result and vice versa.
             *
             * @return The resulting ADD.
             */
            InternalAdd<DdType::CUDD, ValueType> operator!() const;
            
            /*!
             * Performs a logical or of the current anBd the given ADD. As a prerequisite, the operand ADDs need to be
             * 0/1 ADDs.
             *
             * @param other The second ADD used for the operation.
             * @return The logical or of the operands.
             */
            InternalAdd<DdType::CUDD, ValueType> operator||(InternalAdd<DdType::CUDD, ValueType> const& other) const;
            
            /*!
             * Performs a logical or of the current and the given ADD and assigns it to the current ADD. As a
             * prerequisite, the operand ADDs need to be 0/1 ADDs.
             *
             * @param other The second ADD used for the operation.
             * @return A reference to the current ADD after the operation
             */
            InternalAdd<DdType::CUDD, ValueType>& operator|=(InternalAdd<DdType::CUDD, ValueType> const& other);
            
            /*!
             * Adds the two ADDs.
             *
             * @param other The ADD to add to the current one.
             * @return The result of the addition.
             */
            InternalAdd<DdType::CUDD, ValueType> operator+(InternalAdd<DdType::CUDD, ValueType> const& other) const;
            
            /*!
             * Adds the given ADD to the current one.
             *
             * @param other The ADD to add to the current one.
             * @return A reference to the current ADD after the operation.
             */
            InternalAdd<DdType::CUDD, ValueType>& operator+=(InternalAdd<DdType::CUDD, ValueType> const& other);
            
            /*!
             * Multiplies the two ADDs.
             *
             * @param other The ADD to multiply with the current one.
             * @return The result of the multiplication.
             */
            InternalAdd<DdType::CUDD, ValueType> operator*(InternalAdd<DdType::CUDD, ValueType> const& other) const;
            
            /*!
             * Multiplies the given ADD with the current one and assigns the result to the current ADD.
             *
             * @param other The ADD to multiply with the current one.
             * @return A reference to the current ADD after the operation.
             */
            InternalAdd<DdType::CUDD, ValueType>& operator*=(InternalAdd<DdType::CUDD, ValueType> const& other);
            
            /*!
             * Subtracts the given ADD from the current one.
             *
             * @param other The ADD to subtract from the current one.
             * @return The result of the subtraction.
             */
            InternalAdd<DdType::CUDD, ValueType> operator-(InternalAdd<DdType::CUDD, ValueType> const& other) const;
            
            /*!
             * Subtracts the given ADD from the current one and assigns the result to the current ADD.
             *
             * @param other The ADD to subtract from the current one.
             * @return A reference to the current ADD after the operation.
             */
            InternalAdd<DdType::CUDD, ValueType>& operator-=(InternalAdd<DdType::CUDD, ValueType> const& other);
            
            /*!
             * Divides the current ADD by the given one.
             *
             * @param other The ADD by which to divide the current one.
             * @return The result of the division.
             */
            InternalAdd<DdType::CUDD, ValueType> operator/(InternalAdd<DdType::CUDD, ValueType> const& other) const;
            
            /*!
             * Divides the current ADD by the given one and assigns the result to the current ADD.
             *
             * @param other The ADD by which to divide the current one.
             * @return A reference to the current ADD after the operation.
             */
            InternalAdd<DdType::CUDD, ValueType>& operator/=(InternalAdd<DdType::CUDD, ValueType> const& other);
            
            /*!
             * Retrieves the function that maps all evaluations to one that have identical function values.
             *
             * @param other The ADD with which to perform the operation.
             * @return The resulting function represented as an ADD.
             */
            InternalAdd<DdType::CUDD, ValueType> equals(InternalAdd<DdType::CUDD, ValueType> const& other) const;
            
            /*!
             * Retrieves the function that maps all evaluations to one that have distinct function values.
             *
             * @param other The ADD with which to perform the operation.
             * @return The resulting function represented as an ADD.
             */
            InternalAdd<DdType::CUDD, ValueType> notEquals(InternalAdd<DdType::CUDD, ValueType> const& other) const;
            
            /*!
             * Retrieves the function that maps all evaluations to one whose function value in the first ADD are less
             * than the one in the given ADD.
             *
             * @param other The ADD with which to perform the operation.
             * @return The resulting function represented as an ADD.
             */
            InternalAdd<DdType::CUDD, ValueType> less(InternalAdd<DdType::CUDD, ValueType> const& other) const;
            
            /*!
             * Retrieves the function that maps all evaluations to one whose function value in the first ADD are less or
             * equal than the one in the given ADD.
             *
             * @param other The DD with which to perform the operation.
             * @return The resulting function represented as an ADD.
             */
            InternalAdd<DdType::CUDD, ValueType> lessOrEqual(InternalAdd<DdType::CUDD, ValueType> const& other) const;
            
            /*!
             * Retrieves the function that maps all evaluations to one whose function value in the first ADD are greater
             * than the one in the given ADD.
             *
             * @param other The ADD with which to perform the operation.
             * @return The resulting function represented as an ADD.
             */
            InternalAdd<DdType::CUDD, ValueType> greater(InternalAdd<DdType::CUDD, ValueType> const& other) const;
            
            /*!
             * Retrieves the function that maps all evaluations to one whose function value in the first ADD are greater
             * or equal than the one in the given ADD.
             *
             * @param other The ADD with which to perform the operation.
             * @return The resulting function represented as an ADD.
             */
            InternalAdd<DdType::CUDD, ValueType> greaterOrEqual(InternalAdd<DdType::CUDD, ValueType> const& other) const;
            
            /*!
             * Retrieves the function that represents the current ADD to the power of the given ADD.
             *
             * @other The exponent function (given as an ADD).
             * @retur The resulting ADD.
             */
            InternalAdd<DdType::CUDD, ValueType> pow(InternalAdd<DdType::CUDD, ValueType> const& other) const;
            
            /*!
             * Retrieves the function that represents the current ADD modulo the given ADD.
             *
             * @other The modul function (given as an ADD).
             * @retur The resulting ADD.
             */
            InternalAdd<DdType::CUDD, ValueType> mod(InternalAdd<DdType::CUDD, ValueType> const& other) const;
            
            /*!
             * Retrieves the function that represents the logarithm of the current ADD to the bases given by the second
             * ADD.
             *
             * @other The base function (given as an ADD).
             * @retur The resulting ADD.
             */
            InternalAdd<DdType::CUDD, ValueType> logxy(InternalAdd<DdType::CUDD, ValueType> const& other) const;
            
            /*!
             * Retrieves the function that floors all values in the current ADD.
             *
             * @retur The resulting ADD.
             */
            InternalAdd<DdType::CUDD, ValueType> floor() const;
            
            /*!
             * Retrieves the function that ceils all values in the current ADD.
             *
             * @retur The resulting ADD.
             */
            InternalAdd<DdType::CUDD, ValueType> ceil() const;
            
            /*!
             * Retrieves the function that maps all evaluations to the minimum of the function values of the two ADDs.
             *
             * @param other The ADD with which to perform the operation.
             * @return The resulting function represented as an ADD.
             */
            InternalAdd<DdType::CUDD, ValueType> minimum(InternalAdd<DdType::CUDD, ValueType> const& other) const;
            
            /*!
             * Retrieves the function that maps all evaluations to the maximum of the function values of the two ADDs.
             *
             * @param other The ADD with which to perform the operation.
             * @return The resulting function represented as an ADD.
             */
            InternalAdd<DdType::CUDD, ValueType> maximum(InternalAdd<DdType::CUDD, ValueType> const& other) const;
            
            /*!
             * Sum-abstracts from the given meta variables.
             *
             * @param metaVariables The meta variables from which to abstract.
             */
            InternalAdd<DdType::CUDD, ValueType> sumAbstract(InternalBdd<DdType::CUDD> const& cube) const;
            
            /*!
             * Min-abstracts from the given meta variables.
             *
             * @param metaVariables The meta variables from which to abstract.
             */
            InternalAdd<DdType::CUDD, ValueType> minAbstract(InternalBdd<DdType::CUDD> const& cube) const;
            
            /*!
             * Max-abstracts from the given meta variables.
             *
             * @param metaVariables The meta variables from which to abstract.
             */
            InternalAdd<DdType::CUDD, ValueType> maxAbstract(InternalBdd<DdType::CUDD> const& cube) const;
            
            /*!
             * Checks whether the current and the given ADD represent the same function modulo some given precision.
             *
             * @param other The ADD with which to compare.
             * @param precision An upper bound on the maximal difference between any two function values that is to be
             * tolerated.
             * @param relative If set to true, not the absolute values have to be within the precision, but the relative
             * values.
             */
            bool equalModuloPrecision(InternalAdd<DdType::CUDD, ValueType> const& other, double precision, bool relative = true) const;
            
            /*!
             * Swaps the given pairs of meta variables in the ADD. The pairs of meta variables must be guaranteed to have
             * the same number of underlying ADD variables.
             *
             * @param metaVariablePairs A vector of meta variable pairs that are to be swapped for one another.
             * @return The resulting ADD.
             */
            InternalAdd<DdType::CUDD, ValueType> swapVariables(std::vector<InternalAdd<DdType::CUDD, ValueType>> const& from, std::vector<InternalAdd<DdType::CUDD, ValueType>> const& to) const;
            
            /*!
             * Multiplies the current ADD (representing a matrix) with the given matrix by summing over the given meta
             * variables.
             *
             * @param otherMatrix The matrix with which to multiply.
             * @param summationMetaVariables The names of the meta variables over which to sum during the matrix-
             * matrix multiplication.
             * @return An ADD representing the result of the matrix-matrix multiplication.
             */
            InternalAdd<DdType::CUDD, ValueType> multiplyMatrix(InternalAdd<DdType::CUDD, ValueType> const& otherMatrix, std::vector<InternalAdd<DdType::CUDD, ValueType>> const& summationDdVariables) const;
            
            /*!
             * Computes a BDD that represents the function in which all assignments with a function value strictly
             * larger than the given value are mapped to one and all others to zero.
             *
             * @param value The value used for the comparison.
             * @return The resulting BDD.
             */
            InternalBdd<DdType::CUDD> greater(ValueType const& value) const;
            
            /*!
             * Computes a BDD that represents the function in which all assignments with a function value larger or equal
             * to the given value are mapped to one and all others to zero.
             *
             * @param value The value used for the comparison.
             * @return The resulting BDD.
             */
            InternalBdd<DdType::CUDD> greaterOrEqual(ValueType const& value) const;
            
            /*!
             * Computes a BDD that represents the function in which all assignments with a function value strictly
             * lower than the given value are mapped to one and all others to zero.
             *
             * @param value The value used for the comparison.
             * @return The resulting BDD.
             */
            InternalBdd<DdType::CUDD> less(ValueType const& value) const;
            
            /*!
             * Computes a BDD that represents the function in which all assignments with a function value less or equal
             * to the given value are mapped to one and all others to zero.
             *
             * @param value The value used for the comparison.
             * @return The resulting BDD.
             */
            InternalBdd<DdType::CUDD> lessOrEqual(ValueType const& value) const;
            
            /*!
             * Computes a BDD that represents the function in which all assignments with a function value unequal to
             * zero are mapped to one and all others to zero.
             *
             * @return The resulting DD.
             */
            InternalBdd<DdType::CUDD> notZero() const;
            
            /*!
             * Computes the constraint of the current ADD with the given constraint. That is, the function value of the
             * resulting ADD will be the same as the current ones for all assignments mapping to one in the constraint
             * and may be different otherwise.
             *
             * @param constraint The constraint to use for the operation.
             * @return The resulting ADD.
             */
            InternalAdd<DdType::CUDD, ValueType> constrain(InternalAdd<DdType::CUDD, ValueType> const& constraint) const;
            
            /*!
             * Computes the restriction of the current ADD with the given constraint. That is, the function value of the
             * resulting DD will be the same as the current ones for all assignments mapping to one in the constraint
             * and may be different otherwise.
             *
             * @param constraint The constraint to use for the operation.
             * @return The resulting ADD.
             */
            InternalAdd<DdType::CUDD, ValueType> restrict(InternalAdd<DdType::CUDD, ValueType> const& constraint) const;
            
            /*!
             * Retrieves the support of the current ADD.
             *
             * @return The support represented as a BDD.
             */
            InternalBdd<DdType::CUDD> getSupport() const;
            
            /*!
             * Retrieves the number of encodings that are mapped to a non-zero value.
             *
             * @return The number of encodings that are mapped to a non-zero value.
             */
            virtual uint_fast64_t getNonZeroCount(uint_fast64_t numberOfDdVariables) const;
            
            /*!
             * Retrieves the number of leaves of the ADD.
             *
             * @return The number of leaves of the ADD.
             */
            virtual uint_fast64_t getLeafCount() const;
            
            /*!
             * Retrieves the number of nodes necessary to represent the DD.
             *
             * @return The number of nodes in this DD.
             */
            virtual uint_fast64_t getNodeCount() const;
            
            /*!
             * Retrieves the lowest function value of any encoding.
             *
             * @return The lowest function value of any encoding.
             */
            ValueType getMin() const;
            
            /*!
             * Retrieves the highest function value of any encoding.
             *
             * @return The highest function value of any encoding.
             */
            ValueType getMax() const;
            
            /*!
             * Converts the ADD to a BDD by mapping all values unequal to zero to 1. This effectively does the same as
             * a call to notZero().
             *
             * @return The corresponding BDD.
             */
            InternalBdd<DdType::CUDD> toBdd() const;
            
            /*!
             * Retrieves whether this ADD represents the constant one function.
             *
             * @return True if this ADD represents the constant one function.
             */
            bool isOne() const;
            
            /*!
             * Retrieves whether this ADD represents the constant zero function.
             *
             * @return True if this ADD represents the constant zero function.
             */
            bool isZero() const;
            
            /*!
             * Retrieves whether this ADD represents a constant function.
             *
             * @return True if this ADD represents a constants function.
             */
            bool isConstant() const;
            
            /*!
             * Retrieves the index of the topmost variable in the DD.
             *
             * @return The index of the topmost variable in DD.
             */
            virtual uint_fast64_t getIndex() const;
            
            /*!
             * Exports the DD to the given file in the dot format.
             *
             * @param filename The name of the file to which the DD is to be exported.
             */
            void exportToDot(std::string const& filename, std::vector<std::string> const& ddVariableNamesAsStrings) const;
            
            /*!
             * Retrieves an iterator that points to the first meta variable assignment with a non-zero function value.
             *
             * @param enumerateDontCareMetaVariables If set to true, all meta variable assignments are enumerated, even
             * if a meta variable does not at all influence the the function value.
             * @return An iterator that points to the first meta variable assignment with a non-zero function value.
             */
            AddIterator<DdType::CUDD, ValueType> begin(std::shared_ptr<DdManager<DdType::CUDD> const> fullDdManager, std::set<storm::expressions::Variable> const& metaVariables, bool enumerateDontCareMetaVariables = true) const;
            
            /*!
             * Retrieves an iterator that points past the end of the container.
             *
             * @param enumerateDontCareMetaVariables If set to true, all meta variable assignments are enumerated, even
             * if a meta variable does not at all influence the the function value.
             * @return An iterator that points past the end of the container.
             */
             AddIterator<DdType::CUDD, ValueType> end(std::shared_ptr<DdManager<DdType::CUDD> const> fullDdManager, bool enumerateDontCareMetaVariables = true) const;
            
            void composeWithExplicitVector(Odd<DdType::CUDD> const& odd, std::vector<uint_fast64_t> const& ddVariableIndices, std::vector<ValueType>& targetVector, std::function<ValueType (ValueType const&, ValueType const&)> const& function) const;
            
            void composeWithExplicitVector(Odd<DdType::CUDD> const& odd, std::vector<uint_fast64_t> const& ddVariableIndices, std::vector<uint_fast64_t> const& offsets, std::vector<ValueType>& targetVector, std::function<ValueType (ValueType const&, ValueType const&)> const& function) const;
            
            std::vector<InternalAdd<DdType::CUDD, ValueType>> splitIntoGroups(std::vector<uint_fast64_t> const& ddGroupVariableIndices) const;
            
            void toMatrixComponents(std::vector<uint_fast64_t> const& rowGroupIndices, std::vector<uint_fast64_t>& rowIndications, std::vector<storm::storage::MatrixEntry<uint_fast64_t, ValueType>>& columnsAndValues, Odd<DdType::CUDD> const& rowOdd, Odd<DdType::CUDD> const& columnOdd, std::vector<uint_fast64_t> const& ddRowVariableIndices, std::vector<uint_fast64_t> const& ddColumnVariableIndices, bool writeValues) const;
            
            std::vector<std::pair<InternalAdd<DdType::CUDD, ValueType>, InternalAdd<DdType::CUDD, ValueType>>> splitIntoGroups(InternalAdd<DdType::CUDD, ValueType> vector, std::vector<uint_fast64_t> const& ddGroupVariableIndices) const;
            
            static InternalAdd<DdType::CUDD, ValueType> fromVector(InternalDdManager<DdType::CUDD> const* ddManager, std::vector<ValueType> const& values, storm::dd::Odd<DdType::CUDD> const& odd, std::vector<uint_fast64_t> const& ddVariableIndices);
            
        private:
            /*!
             * Retrieves the CUDD ADD object associated with this ADD.
             *
             * @return The CUDD ADD object associated with this ADD.
             */
            ADD getCuddAdd() const;
            
            /*!
             * Retrieves the raw DD node of CUDD associated with this ADD.
             *
             * @return The DD node of CUDD associated with this ADD.
             */
            DdNode* getCuddDdNode() const;
            
            /*!
             * Performs a recursive step to perform the given function between the given DD-based vector and the given
             * explicit vector.
             *
             * @param dd The DD to add to the explicit vector.
             * @param currentLevel The currently considered level in the DD.
             * @param maxLevel The number of levels that need to be considered.
             * @param currentOffset The current offset.
             * @param odd The ODD used for the translation.
             * @param ddVariableIndices The (sorted) indices of all DD variables that need to be considered.
             * @param targetVector The vector to which the translated DD-based vector is to be added.
             */
            void composeWithExplicitVectorRec(DdNode const* dd, std::vector<uint_fast64_t> const* offsets, uint_fast64_t currentLevel, uint_fast64_t maxLevel, uint_fast64_t currentOffset, Odd<DdType::CUDD> const& odd, std::vector<uint_fast64_t> const& ddVariableIndices, std::vector<ValueType>& targetVector, std::function<ValueType (ValueType const&, ValueType const&)> const& function) const;
            
            /*!
             * Splits the given matrix DD into the groups using the given group variables.
             *
             * @param dd The DD to split.
             * @param groups A vector that is to be filled with the DDs for the individual groups.
             * @param ddGroupVariableIndices The (sorted) indices of all DD group variables that need to be considered.
             * @param currentLevel The currently considered level in the DD.
             * @param maxLevel The number of levels that need to be considered.
             * @param remainingMetaVariables The meta variables that remain in the DDs after the groups have been split.
             */
            void splitIntoGroupsRec(DdNode* dd, std::vector<InternalAdd<DdType::CUDD, ValueType>>& groups, std::vector<uint_fast64_t> const& ddGroupVariableIndices, uint_fast64_t currentLevel, uint_fast64_t maxLevel) const;
            
            void splitIntoGroupsRec(DdNode* dd1, DdNode* dd2, std::vector<std::pair<InternalAdd<DdType::CUDD, ValueType>, InternalAdd<DdType::CUDD, ValueType>>>& groups, std::vector<uint_fast64_t> const& ddGroupVariableIndices, uint_fast64_t currentLevel, uint_fast64_t maxLevel) const;
            
            /*!
             * Helper function to convert the DD into a (sparse) matrix.
             *
             * @param dd The DD to convert.
             * @param rowIndications A vector indicating at which position in the columnsAndValues vector the entries
             * of row i start. Note: this vector is modified in the computation. More concretely, each entry i in the
             * vector will be increased by the number of entries in the row. This can be used to count the number
             * of entries in each row. If the values are not to be modified, a copy needs to be provided or the entries
             * need to be restored afterwards.
             * @param columnsAndValues The vector that will hold the columns and values of non-zero entries upon successful
             * completion.
             * @param rowGroupOffsets The row offsets at which a given row group starts.
             * @param rowOdd The ODD used for the row translation.
             * @param columnOdd The ODD used for the column translation.
             * @param currentRowLevel The currently considered row level in the DD.
             * @param currentColumnLevel The currently considered row level in the DD.
             * @param maxLevel The number of levels that need to be considered.
             * @param currentRowOffset The current row offset.
             * @param currentColumnOffset The current row offset.
             * @param ddRowVariableIndices The (sorted) indices of all DD row variables that need to be considered.
             * @param ddColumnVariableIndices The (sorted) indices of all DD row variables that need to be considered.
             * @param generateValues If set to true, the vector columnsAndValues is filled with the actual entries, which
             * only works if the offsets given in rowIndications are already correct. If they need to be computed first,
             * this flag needs to be false.
             */
            void toMatrixComponentsRec(DdNode const* dd, std::vector<uint_fast64_t> const& rowGroupOffsets, std::vector<uint_fast64_t>& rowIndications, std::vector<storm::storage::MatrixEntry<uint_fast64_t, ValueType>>& columnsAndValues, Odd<DdType::CUDD> const& rowOdd, Odd<DdType::CUDD> const& columnOdd, uint_fast64_t currentRowLevel, uint_fast64_t currentColumnLevel, uint_fast64_t maxLevel, uint_fast64_t currentRowOffset, uint_fast64_t currentColumnOffset, std::vector<uint_fast64_t> const& ddRowVariableIndices, std::vector<uint_fast64_t> const& ddColumnVariableIndices, bool writeValues) const;
            
            /*!
             * Builds an ADD representing the given vector.
             *
             * @param manager The manager responsible for the ADD.
             * @param currentOffset The current offset in the vector.
             * @param currentLevel The current level in the DD.
             * @param maxLevel The maximal level in the DD.
             * @param values The vector that is to be represented by the ADD.
             * @param odd The ODD used for the translation.
             * @param ddVariableIndices The (sorted) list of DD variable indices to use.
             * @return The resulting (CUDD) ADD node.
             */
            static DdNode* fromVectorRec(::DdManager* manager, uint_fast64_t& currentOffset, uint_fast64_t currentLevel, uint_fast64_t maxLevel, std::vector<ValueType> const& values, Odd<DdType::CUDD> const& odd, std::vector<uint_fast64_t> const& ddVariableIndices);
            
            InternalDdManager<DdType::CUDD> const* ddManager;
            
            ADD cuddAdd;
        };
    }
}

#endif /* STORM_STORAGE_DD_CUDD_INTERNALCUDDADD_H_ */