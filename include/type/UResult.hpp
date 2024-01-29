#pragma once

#include <string>

namespace utils {
	class UResult {
	public:
		explicit UResult();
		explicit UResult(bool result, int errorCode, std::string&& errorMessage);
		virtual ~UResult();
		
	public:
		int			getErrorCode();
		std::string getErrorMessage();

	public:
		bool success();
		int  successReturnValue(int returnValue);

		bool failed(int errorCode, std::string&& errorMessage);
		int  failedReturnValue(int errorCode, std::string&& errorMessage);

		bool isSucceed();

	private:
		void setSuccess();
		void setError(int errorCode, std::string& errorMessage);
		void setError(int errorCode, std::string&& errorMessage);

	private:
		bool result;

		int errorCode;
		std::string errorMessage;
	};
};