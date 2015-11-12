#include "src/solver/GameSolver.h"

#include "src/solver/LinearEquationSolver.h"
#include "src/utility/solver.h"
#include "src/storage/SparseMatrix.h"
#include "src/utility/vector.h"

namespace storm {
    namespace solver {
        template <typename ValueType>
        GameSolver<ValueType>::GameSolver(storm::storage::SparseMatrix<storm::storage::sparse::state_type> const& player1Matrix, storm::storage::SparseMatrix<ValueType> const& player2Matrix) : AbstractGameSolver(), player1Matrix(player1Matrix), player2Matrix(player2Matrix) {
            // Intentionally left empty.
        }

        template <typename ValueType>
        GameSolver<ValueType>::GameSolver(storm::storage::SparseMatrix<storm::storage::sparse::state_type> const& player1Matrix, storm::storage::SparseMatrix<ValueType> const& player2Matrix, double precision, uint_fast64_t maximalNumberOfIterations, bool relative) : AbstractGameSolver(precision, maximalNumberOfIterations, relative), player1Matrix(player1Matrix), player2Matrix(player2Matrix) {
            // Intentionally left empty.
        }

        template <typename ValueType>
        void GameSolver<ValueType>::solveGame(OptimizationDirection player1Goal, OptimizationDirection player2Goal, std::vector<ValueType>& x, std::vector<ValueType> const& b, std::vector<storm::storage::sparse::state_type>* initialPlayer1Policy, std::vector<storm::storage::sparse::state_type>* initialPlayer2Policy) const {
            uint_fast64_t numberOfPlayer1States = x.size();
            
            if(initialPlayer1Policy != nullptr || initialPlayer2Policy != nullptr){
                //Either we work with both policies or none of them
                assert(initialPlayer1Policy != nullptr && initialPlayer2Policy != nullptr);
                //The policies select certain rows in the matrix of player2.
                //However, note that rows can be selected more then once and in an arbitrary order.
                std::vector<storm::storage::sparse::state_type> selectedRows(numberOfPlayer1States);
                for (uint_fast64_t pl1State = 0; pl1State < numberOfPlayer1States; ++pl1State){
                    auto const& pl1Choice = player1Matrix.getRow(player1Matrix.getRowGroupIndices()[pl1State] + (*initialPlayer1Policy)[pl1State]);
                    assert(pl1Choice.getNumberOfEntries()==1);
                    uint_fast64_t pl2State = pl1Choice.begin()->getColumn();
                    selectedRows[pl1State] = player2Matrix.getRowGroupIndices()[pl2State] + (*initialPlayer2Policy)[pl2State];
                }
                storm::storage::SparseMatrix<ValueType> eqSysMatrix = player2Matrix.selectRowsFromRowIndexSequence(selectedRows, true);
                eqSysMatrix.convertToEquationSystem();
                std::unique_ptr<storm::solver::LinearEquationSolver<ValueType>> solver = storm::utility::solver::LinearEquationSolverFactory<ValueType>().create(eqSysMatrix);
                std::vector<ValueType> subB(numberOfPlayer1States);
                storm::utility::vector::selectVectorValues<ValueType>(subB, selectedRows, b);
                solver->solveEquationSystem(x, subB);
            }
            
            // Set up the environment for value iteration.
            bool converged = false;
            std::vector<ValueType> tmpResult(numberOfPlayer1States);
            std::vector<ValueType> nondetResult(player2Matrix.getRowCount());
            std::vector<ValueType> player2Result(player2Matrix.getRowGroupCount());

            // Now perform the actual value iteration.
            uint_fast64_t iterations = 0;
            do {
                player2Matrix.multiplyWithVector(x, nondetResult);
                storm::utility::vector::addVectors(b, nondetResult, nondetResult);

                if (player2Goal == OptimizationDirection::Minimize) {
                    storm::utility::vector::reduceVectorMin(nondetResult, player2Result, player2Matrix.getRowGroupIndices());
                } else {
                    storm::utility::vector::reduceVectorMax(nondetResult, player2Result, player2Matrix.getRowGroupIndices());
                }

                for (uint_fast64_t pl1State = 0; pl1State < numberOfPlayer1States; ++pl1State) {
                    storm::storage::SparseMatrix<storm::storage::sparse::state_type>::const_rows relevantRows = player1Matrix.getRowGroup(pl1State);
                    if (relevantRows.getNumberOfEntries() > 0) {
                        storm::storage::SparseMatrix<storm::storage::sparse::state_type>::const_iterator it = relevantRows.begin();
                        storm::storage::SparseMatrix<storm::storage::sparse::state_type>::const_iterator ite = relevantRows.end();

                        // Set the first value.
                        tmpResult[pl1State] = player2Result[it->getColumn()];
                        ++it;

                        // Now iterate through the different values and pick the extremal one.
                        if (player1Goal == OptimizationDirection::Minimize) {
                            for (; it != ite; ++it) {
                                tmpResult[pl1State] = std::min(tmpResult[pl1State], player2Result[it->getColumn()]);
                            }
                        } else {
                            for (; it != ite; ++it) {
                                tmpResult[pl1State] = std::max(tmpResult[pl1State], player2Result[it->getColumn()]);
                            }
                        }
                    } else {
                        tmpResult[pl1State] = storm::utility::zero<ValueType>();
                    }
                }

                // Check if the process converged and set up the new iteration in case we are not done.
                converged = storm::utility::vector::equalModuloPrecision(x, tmpResult, precision, relative);
                std::swap(x, tmpResult);

                ++iterations;
            } while (!converged && iterations < maximalNumberOfIterations);
            
            STORM_LOG_WARN_COND(converged, "Iterative solver for stochastic two player games did not converge after " << iterations << "iterations.");
            
            if(this->trackPolicies){
                this->player2Policy = std::vector<storm::storage::sparse::state_type>(player2Matrix.getRowGroupCount());
                storm::utility::vector::reduceVectorMinOrMax(player2Goal, nondetResult, player2Result, player2Matrix.getRowGroupIndices(), &this->player2Policy);

                this->player1Policy = std::vector<storm::storage::sparse::state_type>(numberOfPlayer1States, 0);
                for (uint_fast64_t pl1State = 0; pl1State < numberOfPlayer1States; ++pl1State) {
                    storm::storage::SparseMatrix<storm::storage::sparse::state_type>::const_rows relevantRows = player1Matrix.getRowGroup(pl1State);
                    if (relevantRows.getNumberOfEntries() > 0) {
                        storm::storage::SparseMatrix<storm::storage::sparse::state_type>::const_iterator it = relevantRows.begin();
                        storm::storage::SparseMatrix<storm::storage::sparse::state_type>::const_iterator ite = relevantRows.end();
                        // Set the first value.
                        tmpResult[pl1State] = player2Result[it->getColumn()];
                        ++it;
                        storm::storage::sparse::state_type localChoice = 1;
                        // Now iterate through the different values and pick the extremal one.
                        if (player1Goal == OptimizationDirection::Minimize) {
                            for (; it != ite; ++it, ++localChoice) {
                                if(player2Result[it->getColumn()] < tmpResult[pl1State]){
                                    tmpResult[pl1State] = player2Result[it->getColumn()];
                                    this->player1Policy[pl1State] = localChoice;
                                }
                            }
                        } else {
                            for (; it != ite; ++it, ++localChoice) {
                                if(player2Result[it->getColumn()] > tmpResult[pl1State]){
                                    tmpResult[pl1State] = player2Result[it->getColumn()];
                                    this->player1Policy[pl1State] = localChoice;
                                }
                            }
                        }
                    } else {
                        STORM_LOG_ERROR("There is no choice for Player 1 at state " << pl1State << " in the stochastic two player game. This is not expected!");
                    }
                }
            }
        }

        template class GameSolver<double>;
    }
}