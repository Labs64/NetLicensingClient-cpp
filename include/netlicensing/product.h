#ifndef __PRODUCT_H__
#define __PRODUCT_H__

#include <list>

#include "netlicensing/entity.h"

namespace netlicensing {

	class ProductDiscount {
		String_t totalPrice_i;
		String_t currency_i;
		String_t amountFix_i;
		String_t amountPercent_i;

	public:
		ProductDiscount() :totalPrice_i(), currency_i(),
			amountFix_i(), amountPercent_i() { }

		ProductDiscount(const String_t& totalPrice, const String_t& currency,
			const String_t& amountFix, const String_t& amountPercent)
			: totalPrice_i(totalPrice), currency_i(currency),
			amountFix_i(amountFix), amountPercent_i(amountPercent) { }

		void setTotalPrice(String_t totalPrice) {
			totalPrice_i = totalPrice;
		}

		const String_t& getTotalPrice() const {
			return totalPrice_i;
		}

		void setCurrency(String_t currency) {
			currency_i = currency;
		}

		const String_t& getCurrency() const {
			return currency_i;
		}

		void setAmountFix(String_t amountFix) {
			String_t amountPercent_i;
			amountFix_i = amountFix;
		}

		const String_t& getAmountFix() const {
			return amountFix_i;
		}

		void setAmountPercent(String_t amountPercent) {
			String_t amountFix_i;
			amountPercent_i = amountPercent;

		}

		const String_t& getAmountPercent() const {
			return amountPercent_i;
		}

		String_t toString() {
			std::string totalPrice(this->getTotalPrice());
			std::string currency(this->getCurrency());
			std::string amountFix(this->getAmountFix());
			std::string amountPercent(this->getAmountPercent());
			std::string amount("");

			if (amountFix.length()) {
				amount = amountFix;
			}

			if (amountPercent.length()) {
				amount = amountPercent + "%";
			}

			return totalPrice + ";" + currency + ";" + amount;
		}
	};

	class Product : public BaseEntity {
	private:
		String_t name_i;
		String_t version_i;
		Boolean_t licenceeAutoCreate_i;
		String_t description_i;
		String_t licensingInfo_i;
		std::list<ProductDiscount> productDiscounts_i;
		bool productDiscountsToched = false;

	public:
		Product() : name_i(), version_i(), licenceeAutoCreate_i(false),
			description_i(), licensingInfo_i(), productDiscounts_i() { }

		void setName(const String_t& name) {
			name_i = name;
		}

		const String_t& getName() const {
			return name_i;
		}

		void setVersion(const String_t& version) {
			version_i = version;
		}

		const String_t& getVersion() const {
			return version_i;
		}

		void setLicenseeAutoCreate(const Boolean_t& licenseeAutoCreate) {
			licenceeAutoCreate_i = licenseeAutoCreate;
		}

		const Boolean_t& getLicenseeAutoCreate() const {
			return licenceeAutoCreate_i;
		}

		void setDescription(const String_t& description) {
			description_i = description;
		}

		const String_t& getDescription() const {
			return description_i;
		}

		void setLicensingInfo(const String_t& licensingInfo) {
			licensingInfo_i = licensingInfo;
		}

		const String_t& getLicensingInfo() const {
			return licensingInfo_i;
		}

		const std::list<ProductDiscount>& getDiscounts() const {
			return productDiscounts_i;
		}

		std::list<ProductDiscount>& getDiscounts() {
			return productDiscounts_i;
		}

		void addDiscount(ProductDiscount& discount) {
			productDiscounts_i.push_back(discount);
			productDiscountsToched = true;
		}

		void setProductsDiscounts(std::list<ProductDiscount>& productDiscounts) {
			productDiscounts_i = productDiscounts;
			productDiscountsToched = true;
		}

		bool isProductDiscountsToched() {
			return productDiscountsToched;
		}
	};

}

#endif // __PRODUCT_H__