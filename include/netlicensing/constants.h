#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#include <list>
#include <string>
#include "netlicensing/datatypes.h"

namespace netlicensing {

  //Common
  static const char* const ID      = "id";
  static const char* const ACTIVE  = "active";
  static const char* const NUMBER  = "number";
  static const char* const NAME    = "name";
  static const char* const VERSION = "version";
  DEPRECATED(static const char* const LICENSEE_AUTOCREATE) = "licenseeAutoCreate";
  static const char* const DELETED = "deleted";
  static const char* const CASCADE = "forceCascade";
  static const char* const PRICE   = "price";
  static const char* const DISCOUNT = "discount";
  static const char* const CURRENCY = "currency";
  static const char* const IN_USE  = "inUse";
  static const char* const FILTER  = "filter";
  static const char* const BASE_URL = "baseUrl";
  static const char* const USERNAME = "username";
  static const char* const PASSWORD = "password";
  static const char* const SECURITY_MODE = "securityMode";
  static const char* const PROP_ID     = "ID";
  static const char* const PROP_TTL    = "TTL";
  static const char* const LICENSE_TYPE = "licenseType";
  static const char* const HIDDEN = "hidden";

  //Utility
  static const char* const UTILITY_ENDPOINT_PATH = "utility";
  static const char* const ENDPOINT_PATH_LICENSE_TYPES = "licenseTypes";
  static const char* const ENDPOINT_PATH_LICENSING_MODELS = "licensingModels";
  static const char* const ENDPOINT_PATH_COUNTRIES = "countries";
  static const char* const LICENSING_MODEL_PROPERTIES = "LicensingModelProperties";

  //Token
  static const char* const TOKEN_ENDPOINT_PATH = "token";
  static const char* const EXPIRATION_TIME = "expirationTime";
  static const char* const TOKEN_TYPE = "tokenType";
  static const char* const API_KEY = "apiKey";
  static const char* const TOKEN_PROP_EMAIL = "email";
  static const char* const TOKEN_PROP_VENDORNUMBER = "vendorNumber";
  static const char* const TOKEN_PROP_SHOP_URL = "shopURL";

  //Vendor
  static const char* const VENDOR_NUMBER = "vendorNumber";
  static const char* const VENDOR_TYPE = "Vendor";

  //Product
  static const char* const PRODUCT_ENDPOINT_PATH = "product";
  static const char* const PRODUCT_NUMBER = "productNumber";
  static const char* const LICENSEE_AUTO_CREATE = "licenseeAutoCreate";
  static const char* const DESCRIPTION = "description";
  static const char* const LICENSING_INFO = "licensingInfo";
  static const char* const DISCOUNTS = "discounts";
  static const char* const PROP_LICENSEE_SECRET_MODE = "licenseeSecretMode";
  static const char* const PROP_VAT_MODE = "vatMode";

  //Discount
  static const char* const TOTAL_PRICE = "totalPrice";
  static const char* const AMOUNT_FIX = "amountFix";
  static const char* const AMOUNT_PERCENT = "amountPercent";

  //ProductModule
  static const char* const PRODUCT_MODULE_ENDPOINT_PATH = "productmodule";
  static const char* const PRODUCT_MODULE_NUMBER = "productModuleNumber";
  static const char* const PRODUCT_MODULE_NAME = "productModuleName";
  static const char* const LICENSING_MODEL = "licensingModel";

  //LicenseTemplate
  static const char* const LICENSE_TEMPLATE_ENDPOINT_PATH = "licensetemplate";
  static const char* const LICENSE_TEMPLATE_NUMBER = "licenseTemplateNumber";
  static const char* const AUTOMATIC = "automatic";
  static const char* const HIDE_LICENSES = "hideLicenses";

  //Licensee
  static const char* const LICENSEE_ENDPOINT_PATH = "licensee";
  static const char* const ENDPOINT_PATH_VALIDATE = "validate";
  static const char* const ENDPOINT_PATH_TRANSFER = "transfer";
  static const char* const LICENSEE_NUMBER = "licenseeNumber";
  static const char* const SOURCE_LICENSEE_NUMBER = "sourceLicenseeNumber";
  static const char* const PROP_LICENSEE_NAME = "licenseeName";
  static const char* const PROP_LICENSEE_SECRET = "licenseeSecret";
  static const char* const PROP_MARKED_FOR_TRANSFER = "markedForTransfer";

  //License
  static const char* const LICENSE_ENDPOINT_PATH = "license";
  static const char* const LICENSE_NUMBER = "licenseNumber";

  //Transaction
  static const char* const TRANSACTION_ENDPOINT_PATH = "transaction";
  static const char* const TRANSACTION_NUMBER = "transactionNumber";
  static const char* const GRAND_TOTAL = "grandTotal";
  static const char* const STATUS = "status";
  static const char* const SOURCE = "source";
  static const char* const DATE_CREATED = "datecreated";
  static const char* const DATE_CLOSED = "dateclosed";
  static const char* const VAT = "vat";
  static const char* const VAT_MODE = "vatMode";
  static const char* const LICENSE_TRANSACTION_JOIN = "licenseTransactionJoin";
  static const char* const SOURCE_SHOP_ONLY = "shopOnly";

  //PaymentMethod
  static const char* const PAYMENT_METHOD_ENDPOINT_PATH = "paymentmethod";

  //Shop
  static const char* const PROP_SHOP_LICENSE_ID = "shop-license-id";
  static const char* const PROP_SHOPPING_CART = "shopping-cart";

  //ValidationResult
  static const char* const VALIDATION_RESULT_TYPE = "ProductModuleValidation";
  static const int DEFAULT_TTL_MINUTES = 60 * 24; // 1 day

  //LicensingModel
  static const char* const VALID = "valid";
  static const char* const LICENSING_MODEL_TRY_AND_BUY_NAME = "TryAndBuy";
  static const char* const LICENSING_MODEL_RENTAL_NAME = "Rental";
  static const char* const LICENSING_MODEL_SUBSCRIPTION_NAME = "Subscription";
  static const char* const LICENSING_MODEL_FLOATING_NAME = "Floating";
  static const char* const LICENSING_MODEL_MULTI_FEATURE_NAME = "MultiFeature";
  static const char* const LICENSING_MODEL_PAY_PER_USE_NAME = "PayPerUse";
  static const char* const LICENSING_MODEL_PRICING_TABLE_NAME = "PricingTable";
  static const char* const LICENSING_MODEL_PRICING_TABLE_PLAN = "plan";
  static const char* const LICENSING_MODEL_PRICING_TABLE_SKU = "sku";
  static const char* const LICENSING_MODEL_QUOTA_NAME = "Quota";

}  // namespace netlicensing

#endif  // __CONSTANTS_H__
