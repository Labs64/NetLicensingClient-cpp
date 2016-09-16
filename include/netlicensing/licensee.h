#ifndef __LICENSEE_H__
#define __LICENSEE_H__

#include "netlicensing/entity.h"
#include "netlicensing/constants.h"

namespace netlicensing 
{
	struct DummyProperty : public FlatList<DummyProperty>
	{
		void add_property(const std::string& name, const std::string& value) {};
	};

	struct Licensee : public Entity 
	{
	private:
		bool		active_;
		std::string number_;
		std::string product_;
		std::string name_;

	public:

		// Developer Note: 16/09/16 TechToast
		//
		// Due to the way the Mapper and Traversal systems have been implemented
		// all Entity types are required to have a PropertyType defined. However
		// at the time of writing, the only pre-defined property I could see was
		// the Product->Discount property. I guess because Product was the only entity
		// type to be implemeted until now, this issue hasn't been noticed before.
		//
		// I did consider modifying the Product class to fix this, but decided to
		// restrict my submission to additions only for the time being.
		//
		typedef DummyProperty PropertyType;

		Licensee() 
			: active_(true)
		{}

		void add_list(std::shared_ptr<PropertyType> ptr) {}		// Dummy method
		void add_property(const std::string& name, const std::string& value);
		parameters_type to_parameters_list() const;

		bool			getInUse() const						{ return active_; }
		std::string		getName() const							{ return name_; }
		std::string		getNumber() const						{ return number_; }
		std::string		getProduct() const						{ return product_; }

		void			setActive(bool active)					{ active_  = active; }
		void			setName(const std::string& name)		{ name_    = name; }
		void			setNumber(const std::string& number)	{ number_  = number; }
		void			setProduct(const std::string& product)	{ product_ = product; }
	};

}

#endif //__LICENSEE_H__