#ifndef __MAPPER_H__
#define __MAPPER_H__

#include <string>
#include <list>
#include <json/json.h>

#include "netlicensing/info.h"
#include "netlicensing/licensee.h"
#include "netlicensing/product.h"
#include "netlicensing/validation_result.h"

namespace netlicensing {

  /**
  * @brief internal service class for proxing traverse callbacks to items and lists hierarchy
  */

  class ItemWrapper {
  public:
    typedef std::shared_ptr<ItemWrapper> Ptr_t;

    virtual ~ItemWrapper() {}
    virtual void addProperty(const std::string& key, const std::string& value) = 0;

    virtual Ptr_t createNested() {
      return Ptr_t();  // default behavior: no nested elements expected
    }

    virtual void addNested(const std::string& name, const Ptr_t& nested) {
      // default behavior: no nested elements expected
    }
  };

  class MapperBase {
    std::list<Info> infos_i;

  public:
    MapperBase() : infos_i() { }

    void addInfo(const std::string& id, const std::string& type, const std::string& value) {
      infos_i.push_back(Info(id, type, value));
    }

    const std::list<Info>& getInfos() const {
      return infos_i;
    }
  };


  class ProductDiscountWrapper : public ItemWrapper {
    String_t totalPrice_i;
    String_t currency_i;
    String_t amountFix_i;
    String_t amountPercent_i;

  public:
    ProductDiscount getProductDiscount() const {
      return ProductDiscount(totalPrice_i, currency_i, amountFix_i, amountPercent_i);
    }

    virtual void addProperty(const std::string& key, const std::string& value) {
      if (key == "totalPrice") {
        totalPrice_i = value;
      } else if (key == "currency") {
        currency_i = value;
      } else if (key == "amountFix") {
        amountFix_i = value;
      } else if (key == "amountPercent") {
        amountPercent_i = value;
      }
    }
  };

  class ProductWrapper : public ItemWrapper {
    Product item_i;

  public:
    const Product& getItem() {
      return item_i;
    }

    virtual void addProperty(const std::string& key, const std::string& value) {
      if (key == "number") {
        item_i.setNumber(value);
      } else if (key == "active") {
        item_i.setActive(value.c_str());
      } else if (key == "name") {
        item_i.setName(value);
      } else if (key == "version") {
        item_i.setVersion(value);
      } else if (key == "licenseeAutoCreate") {
        item_i.setLicenseeAutoCreate(value.c_str());
      } else if (key == "description") {
        item_i.setDescription(value);
      } else if (key == "licensingInfo") {
        item_i.setLicensingInfo(value);
      }
    }

    virtual Ptr_t createNested() {
      return std::make_shared<ProductDiscountWrapper>();
    }

    virtual void addNested(const std::string& name, const Ptr_t& nested) {
      if (name == "discount") {
        ProductDiscount productDiscount =
            std::dynamic_pointer_cast<ProductDiscountWrapper>(nested)->getProductDiscount();
        item_i.getDiscounts().push_back(productDiscount);
      }
    }
  };

  class LicenseeWrapper : public ItemWrapper {
    Licensee item_i;

  public:
    const Licensee& getItem() {
      return item_i;
    }

    virtual void addProperty(const std::string& key, const std::string& value) {
      if (key == "number") {
        item_i.setNumber(value);
      } else if (key == "active") {
        item_i.setActive(value.c_str());
      } else if (key == "name") {
        item_i.setName(value);
      }
    }
  };

  template<class T>
  struct ItemTraits;

  template<>
  struct ItemTraits<Product> {
    typedef ProductWrapper Wrapper_t;
    static std::string getType() { return "Product"; }
  };

  template<>
  struct ItemTraits<Licensee> {
    typedef LicenseeWrapper Wrapper_t;
    static std::string getType() { return "Licensee"; }
  };

  template<typename T>
  class StandardMapper : public MapperBase {
    std::list<T> items_i;

  public:
    typedef T Item_t;

    StandardMapper() : MapperBase(), items_i() { }

    const std::list<T>& getItems() const {
      return items_i;
    }

    ItemWrapper::Ptr_t createItem(const std::string& type) {
      if (type == ItemTraits<T>::getType()) {
        return std::make_shared<typename ItemTraits<T>::Wrapper_t>();
      }
      return ItemWrapper::Ptr_t();
    }

    void addItem(const ItemWrapper::Ptr_t& item) {
      items_i.push_back(
          std::dynamic_pointer_cast<typename ItemTraits<T>::Wrapper_t>(item)->getItem());
    }
  };


  class CompositionWrapper : public ItemWrapper {
    Composition composition_i;

  public:
    const Composition& getComposition() {
      return composition_i;
    }

    virtual void addProperty(const std::string& key, const std::string& value) {
      composition_i.put(key, value);
    }

    virtual Ptr_t createNested() {
      return std::make_shared<CompositionWrapper>();
    }

    virtual void addNested(const std::string& name, const Ptr_t& nested) {
      composition_i.put(name, 
          std::dynamic_pointer_cast<CompositionWrapper>(nested)->getComposition());
    }
  };

  class ValidationResultMapper : public MapperBase {
    ValidationResult& validationResult_i;

  public:
    ValidationResultMapper(ValidationResult& validationResult)
      : MapperBase(), validationResult_i(validationResult) { }

    ItemWrapper::Ptr_t createItem(const std::string& type) {
      if (type == "ProductModuleValidation") {
        return std::make_shared<CompositionWrapper>();
      }
      return ItemWrapper::Ptr_t();
    }

    void addItem(const ItemWrapper::Ptr_t& item) {
      const Composition& comp =
          std::dynamic_pointer_cast<CompositionWrapper>(item)->getComposition();
      auto productModuleNumber = comp.get("productModuleNumber");
      if (productModuleNumber) {
        validationResult_i.setProductModuleValidation(*productModuleNumber, comp);
      }
    }
  };

}  // namespace netlicensing

#endif //__MAPPER_H__