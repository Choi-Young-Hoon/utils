#include "type/UResult.hpp"

namespace utils {
	UResult::UResult() {
		this->setSuccess();
	}

	UResult::UResult(bool result, int errorCode, std::string&& errorMessage) {
		this->result	   = result;
		this->errorCode	   = errorCode;
		this->errorMessage = errorMessage;
	}

	UResult::~UResult() {

	}

	int UResult::getErrorCode() {
		return this->errorCode;
	}

	std::string UResult::getErrorMessage() {
		return this->errorMessage;
	}

	bool UResult::success() {
		this->setSuccess();
		return this->isSucceed();
	}

	int UResult::successReturnValue(int returnValue) {
		this->setSuccess();
		return returnValue;
	}

	bool UResult::failed(int errorCode, std::string&& errorMessage) {
		this->setError(errorCode, errorMessage);
		return this->isSucceed();
	}

	int UResult::failedReturnValue(int errorCode, std::string&& errorMessage) {
		this->setError(errorCode, errorMessage);
		return errorCode;
	}

	bool UResult::isSucceed() {
		return this->result;
	}

	void UResult::setSuccess() {
		this->result       = true;
		this->errorCode    = 0;
		this->errorMessage = "";
	}

	void UResult::setError(int errorCode, std::string& errorMessage) {
		this->result	   = false;
		this->errorCode	   = errorCode;
		this->errorMessage = errorMessage;
	}

	void UResult::setError(int errorCode, std::string&& errorMessage) {
		this->result	   = false;
		this->errorCode	   = errorCode;
		this->errorMessage = errorMessage;
	}
};