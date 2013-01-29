/*
 * Until.h
 *
 *  Created on: 19.10.2012
 *      Author: Thomas Heinemann
 */

#ifndef STORM_FORMULA_UNTIL_H_
#define STORM_FORMULA_UNTIL_H_

#include "AbstractPathFormula.h"
#include "AbstractStateFormula.h"
#include "src/formula/AbstractFormulaChecker.h"

namespace storm {

namespace formula {

template <class T> class Until;

template <class T>
class IUntilModelChecker {
    public:
        virtual std::vector<T>* checkUntil(const Until<T>& obj) const = 0;
};

/*!
 * @brief
 * Class for a Abstract (path) formula tree with an Until node as root.
 *
 * Has two Abstract state formulas as sub formulas/trees.
 *
 * @par Semantics
 * The formula holds iff eventually, formula \e right (the right subtree) holds, and before,
 * \e left holds always.
 *
 * The subtrees are seen as part of the object and deleted with the object
 * (this behavior can be prevented by setting them to NULL before deletion)
 *
 * @see AbstractPathFormula
 * @see AbstractFormula
 */
template <class T>
class Until : public AbstractPathFormula<T> {

public:
	/*!
	 * Empty constructor
	 */
	Until() {
		this->left = NULL;
		this->right = NULL;
	}

	/*!
	 * Constructor
	 *
	 * @param left The left formula subtree
	 * @param right The left formula subtree
	 */
	Until(AbstractStateFormula<T>* left, AbstractStateFormula<T>* right) {
		this->left = left;
		this->right = right;
	}

	/*!
	 * Destructor.
	 *
	 * Also deletes the subtrees.
	 * (this behaviour can be prevented by setting the subtrees to NULL before deletion)
	 */
	virtual ~Until() {
	  if (left != NULL) {
		  delete left;
	  }
	  if (right != NULL) {
		  delete right;
	  }
	}

	/*!
	 * Sets the left child node.
	 *
	 * @param newLeft the new left child.
	 */
	void setLeft(AbstractStateFormula<T>* newLeft) {
		left = newLeft;
	}

	/*!
	 * Sets the right child node.
	 *
	 * @param newRight the new right child.
	 */
	void setRight(AbstractStateFormula<T>* newRight) {
		right = newRight;
	}

	/*!
	 * @returns a pointer to the left child node
	 */
	const AbstractStateFormula<T>& getLeft() const {
		return *left;
	}

	/*!
	 * @returns a pointer to the right child node
	 */
	const AbstractStateFormula<T>& getRight() const {
		return *right;
	}

	/*!
	 * @returns a string representation of the formula
	 */
	virtual std::string toString() const {
		std::string result = "(";
		result += left->toString();
		result += " U ";
		result += right->toString();
		result += ")";
		return result;
	}

	/*!
	 * Clones the called object.
	 *
	 * Performs a "deep copy", i.e. the subtrees of the new object are clones of the original ones
	 *
	 * @returns a new BoundedUntil-object that is identical the called object.
	 */
	virtual AbstractPathFormula<T>* clone() const {
		Until<T>* result = new Until();
		if (left != NULL) {
			result->setLeft(left->clone());
		}
		if (right != NULL) {
			result->setRight(right->clone());
		}
		return result;
	}

	/*!
	 * Calls the model checker to check this formula.
	 * Needed to infer the correct type of formula class.
	 *
	 * @note This function should only be called in a generic check function of a model checker class. For other uses,
	 *       the methods of the model checker should be used.
	 *
	 * @returns A vector indicating the probability that the formula holds for each state.
	 */
	virtual std::vector<T> *check(const storm::modelChecker::AbstractModelChecker<T>& modelChecker) const {
		return modelChecker.template as<IUntilModelChecker>()->checkUntil(*this);
	}
	
	virtual bool conforms(const AbstractFormulaChecker<T>& checker) const {
        return checker.conforms(this->left) && checker.conforms(this->right);
    }

private:
	AbstractStateFormula<T>* left;
	AbstractStateFormula<T>* right;
};

} //namespace formula

} //namespace storm

#endif /* STORM_FORMULA_UNTIL_H_ */
