/*
 * ExpressionVisitor.h
 *
 *  Created on: 26.01.2013
 *      Author: Christian Dehnert
 */

#ifndef STORM_IR_EXPRESSIONS_EXPRESSIONVISITOR_H_
#define STORM_IR_EXPRESSIONS_EXPRESSIONVISITOR_H_

namespace storm {
    namespace ir {
        namespace expressions {
            
            class BaseExpression;
            class BinaryBooleanFunctionExpression;
            class BinaryNumericalFunctionExpression;
            class BinaryRelationExpression;
            class BooleanConstantExpression;
            class BooleanLiteral;
            class DoubleConstantExpression;
            class DoubleLiteral;
            class IntegerConstantExpression;
            class IntegerLiteral;
            class UnaryBooleanFunctionExpression;
            class UnaryNumericalFunctionExpression;
            class VariableExpression;
            
            class ExpressionVisitor {
            public:
                virtual void visit(BaseExpression* expression) = 0;
                virtual void visit(BinaryBooleanFunctionExpression* expression) = 0;
                virtual void visit(BinaryNumericalFunctionExpression* expression) = 0;
                virtual void visit(BinaryRelationExpression* expression) = 0;
                virtual void visit(BooleanConstantExpression* expression) = 0;
                virtual void visit(BooleanLiteral* expression) = 0;
                virtual void visit(DoubleConstantExpression* expression) = 0;
                virtual void visit(DoubleLiteral* expression) = 0;
                virtual void visit(IntegerConstantExpression* expression) = 0;
                virtual void visit(IntegerLiteral* expression) = 0;
                virtual void visit(UnaryBooleanFunctionExpression* expression) = 0;
                virtual void visit(UnaryNumericalFunctionExpression* expression) = 0;
                virtual void visit(VariableExpression* expression) = 0;
            };
            
        } // namespace expressions
    } // namespace ir
} // namespace storm

#endif /* STORM_IR_EXPRESSIONS_EXPRESSIONVISITOR_H_ */
