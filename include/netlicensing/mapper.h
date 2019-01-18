#ifndef __MAPPER_H__
#define __MAPPER_H__

#include <string>
#include <list>
#include <json/json.h>

#include "netlicensing/info.h"
#include "netlicensing/licensee.h"
#include "netlicensing/product.h"
#include "netlicensing/product_module.h"
#include "netlicensing/license.h"
#include "netlicensing/country.h"
#include "netlicensing/validation_result.h"
#include "netlicensing/payment_method.h"
#include "netlicensing/token.h"
#include "netlicensing/transaction.h"

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

  class ProductModuleWrapper : public ItemWrapper {
    ProductModule item_i;

  public:
    const ProductModule& getItem() {
      return item_i;
    }

    virtual void addProperty(const std::string& key, const std::string& value) {
        if (key == "number") {
          item_i.setNumber(value);
        } else if (key == "active") {
          item_i.setActive(value.c_str());
        } else if (key == "name") {
          item_i.setName(value);
        } else if (key == "licensingModel") {
          item_i.setLicensingModel(value);
        } else if (key == "productNumber") {
          item_i.setProductNumber(value);
        }
    }
  };

  class LicenseTemplateWrapper : public ItemWrapper {
    LicenseTemplate item_i;

  public:
    const LicenseTemplate& getItem() {
      return item_i;
    }

    virtual void addProperty(const std::string& key, const std::string& value) {
      if (key == "number") {
        item_i.setNumber(value);
      } else if (key == "active") {
        item_i.setActive(value.c_str());
      } else if (key == "name") {
        item_i.setName(value);
      } else if (key == "licenseType") {
        item_i.setLicenseType(value);
      } else if (key == "productModuleNumber") {
        item_i.setProductModuleNumber(value);
      } else if (key == "price") {
        item_i.setPrice(value);
      } else if (key == "currency") {
        item_i.setCurrency(value);
      } else if (key == "automatic") {
        item_i.setAutomatic((value == "true"?true:false));
      } else if (key == "hidden") {
        item_i.setHidden((value == "true"?true:false));
      } else if (key == "hideLicenses") {
        item_i.setHideLicenses((value == "true"?true:false));
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
      } else if (key == "productNumber") {
        item_i.setProductNumber(value);
      }
    }
  };

  class LicenseWrapper : public ItemWrapper {
    License item_i;

  public:
    const License& getItem() {
      return item_i;
    }

    virtual void addProperty(const std::string& key, const std::string& value) {
      if (key == "number") {
        item_i.setNumber(value);
      } else if (key == "active") {
        item_i.setActive(value.c_str());
      } else if (key == "name") {
        item_i.setName(value);
      } else if (key == "price") {
        item_i.setPrice(value);
      } else if (key == "currency") {
        item_i.setCurrency(value);
      } else if (key == "hidden") {
        item_i.setHidden((value == "true"?true:false));
      } else if (key == "licenseeNumber") {
        item_i.setLicenseeNumber(value);
      } else if (key == "licenseTemplateNumber") {
        item_i.setLicenseTemplateNumber(value);
      }
    }
  };

  class CountryWrapper : public ItemWrapper {
    Country item_i;

  public:
    const Country& getItem() {
      return item_i;
    }

    virtual void addProperty(const std::string& key, const std::string& value) {
      if (key == "isEu") {
        item_i.setIsEu(value == "true");
      } else if (key == "code") {
        item_i.setCode(value);
      } else if (key == "name") {
        item_i.setName(value);
      } else if (key == "vatPercent") {
        item_i.setVatPercent(value);
      }
    }
  };

  class PaymentMethodWrapper : public ItemWrapper {
    PaymentMethod item_i;

  public:
    const PaymentMethod& getItem() {
      return item_i;
    }

    virtual void addProperty(const std::string& key, const std::string& value) {
      if (key == "number") {
        item_i.setNumber(value);
      } else if (key == "active") {
        item_i.setActive(value.c_str());
      }
    }
  };

  class TokenWrapper : public ItemWrapper {
    Token item_i;

  public:
    const Token& getItem() {
      return item_i;
    }

    virtual void addProperty(const std::string& key, const std::string& value) {
      if (key == "number") {
        item_i.setNumber(value);
      } else if (key == "active") {
        item_i.setActive(value.c_str());
      } else if (key == "vendorNumber") {
        item_i.setVendorNumber(value);
      } else if (key == "expirationTime") {
        item_i.setExpirationTime(value);
      } else if (key == "tokenType") {
        item_i.setTokenType(value);
      }
    }
  };

  class TransactionWrapper : public ItemWrapper {
    Transaction item_i;

  public:
    const Transaction& getItem() {
      return item_i;
    }

    virtual void addProperty(const std::string& key, const std::string& value) {
      if (key == "number") {
        item_i.setNumber(value);
      } else if (key == "active") {
        item_i.setActive(value.c_str());
      } else if (key == "status") {
        item_i.setStatus(value);
      } else if (key == "source") {
        item_i.setSource(value);
      } else if (key == "grandTotal") {
        item_i.setGrandTotal(value);
      } else if (key == "discount") {
        item_i.setDiscount(value);
      } else if (key == "currency") {
        item_i.setCurrency(value);
      } else if (key == "dateCreated") {
        item_i.setDateCreated(value);
      } else if (key == "dateClosed") {
        item_i.setDateClosed(value);
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
  struct ItemTraits<ProductModule> {
    typedef ProductModuleWrapper Wrapper_t;
    static std::string getType() { return "ProductModule"; }
  };

  template<>
  struct ItemTraits<LicenseTemplate> {
    typedef LicenseTemplateWrapper Wrapper_t;
    static std::string getType() { return "LicenseTemplate"; }
  };

  template<>
  struct ItemTraits<Licensee> {
    typedef LicenseeWrapper Wrapper_t;
    static std::string getType() { return "Licensee"; }
  };

  template<>
  struct ItemTraits<License> {
    typedef LicenseWrapper Wrapper_t;
    static std::string getType() { return "License"; }
  };

  template<>
  struct ItemTraits<Country> {
    typedef CountryWrapper Wrapper_t;
    static std::string getType() { return "Country"; }
  };

  template<>
  struct ItemTraits<PaymentMethod> {
    typedef PaymentMethodWrapper Wrapper_t;
    static std::string getType() { return "PaymentMethod"; }
  };

  template<>
  struct ItemTraits<Token> {
    typedef TokenWrapper Wrapper_t;
    static std::string getType() { return "Token"; }
  };

  template<>
  struct ItemTraits<Transaction> {
    typedef TransactionWrapper Wrapper_t;
    static std::string getType() { return "Transaction"; }
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
