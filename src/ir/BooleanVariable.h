/*
 * BooleanVariable.h
 *
 *  Created on: 08.01.2013
 *      Author: Christian Dehnert
 */

#ifndef STORM_IR_BOOLEANVARIABLE_H_
#define STORM_IR_BOOLEANVARIABLE_H_

#include "src/ir/Variable.h"
#include <memory>
#include <map>

namespace storm {

namespace ir {

/*!
 * A class representing a boolean variable.
 */
class BooleanVariable : public Variable {
public:
	/*!
	 * Default constructor. Creates a boolean variable without a name.
	 */
	BooleanVariable();

	/*!
	 * Creates a boolean variable with the given name and the given initial value.
	 * @param index a unique (among the variables of equal type) index for the variable.
	 * @param variableName the name of the variable.
	 * @param initialValue the expression that defines the initial value of the variable.
	 */
	BooleanVariable(uint_fast64_t index, std::string variableName, std::shared_ptr<storm::ir::expressions::BaseExpression> initialValue = std::shared_ptr<storm::ir::expressions::BaseExpression>(nullptr));


	BooleanVariable(const BooleanVariable& var, const std::string& newName, const std::map<std::string, std::string>& renaming, const std::map<std::string,uint_fast64_t>& bools, const std::map<std::string,uint_fast64_t>& ints);

	/*!
	 * Retrieves a string representation of this variable.
	 * @returns a string representation of this variable.
	 */
	std::string toString() const;
};

} // namespace ir

} // namespace storm

#endif /* STORM_IR_BOOLEANVARIABLE_H_ */