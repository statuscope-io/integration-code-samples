// Sample C++ code that marks a task on statuscope.io as successful or failed

#include <curl/curl.h>
#include <iostream>

// A wrapper class that marks Statuscope tasks as successful or failed
class Statuscope
{
    public:
        static const std::string BASE_URL;

    public:
        Statuscope(const std::string& token);
        virtual ~Statuscope();

    public:
        bool Success(const std::string& taskId);
        bool Failure(const std::string& taskId, const std::string& reason);

    private:
        bool _post(const std::string& url, const std::string& data);

    private:
        CURL* _curlHandle;
        std::string _token;
        bool _initialized;
};

const std::string Statuscope::BASE_URL = "https://www.statuscope.io/tasks/";

Statuscope::Statuscope(const std::string& token) : _token(token), _initialized(false)
{
    // Initialize libCURL
    curl_global_init(CURL_GLOBAL_ALL);
    _curlHandle = curl_easy_init();
    if (!_curlHandle) {
        std::cerr << "Cannot get a cURL handle" << std::endl;
        _initialized = false;
    }

    _initialized = true;
}

Statuscope::~Statuscope()
{
    curl_easy_cleanup(_curlHandle);
    curl_global_cleanup();
}

bool Statuscope::_post(const std::string& url, const std::string& data)
{
    CURLcode res;
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");

    // Prepare for a POST request to send JSON data
    curl_easy_setopt(_curlHandle, CURLOPT_POSTFIELDSIZE, data.length());
    curl_easy_setopt(_curlHandle, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(_curlHandle, CURLOPT_URL, url.c_str());
    curl_easy_setopt(_curlHandle, CURLOPT_POSTFIELDS, data.c_str());

    std::cout << "Making a request to '" << url << "' with data '" << data << "'" << std::endl;

    res = curl_easy_perform(_curlHandle);
    curl_slist_free_all(headers);

    if (res != CURLE_OK) {
        std::cerr << "POST request failed: " << curl_easy_strerror(res) << std::endl;
        return false;
    }

    return true;
}

bool Statuscope::Success(const std::string& taskId)
{
    const std::string url = Statuscope::BASE_URL + taskId;
    const std::string postData = "{\"token\":\"" + _token + "\", \"status\":\"OK\"}";

    if (!_post(url, postData)) {
        std::cerr << "Cannot mark task as successful" << std::endl;
        return false;
    }

    return true;
}

bool Statuscope::Failure(const std::string& taskId, const std::string& reason)
{
    const std::string url = Statuscope::BASE_URL + taskId;
    const std::string postData = "{\"token\":\"" + _token + "\", \"status\":\"KO\", \"reason\": \"" + reason + "\"}";

    if (!_post(url, postData)) {
        std::cerr << "Cannot mark task as failed" << std::endl;
        return false;
    }

    return true;
}

int main()
{
    // Create a Statuscope instance with API key
    Statuscope statuscope("3577fbba98ffa4f7f00a7bfd7420ff45");

    // Make a request to mark a task as successful
    if (statuscope.Success("vR6gsTgSDcsbENCpw")) {
        std::cout << "\nRequest succeeded to mark a task as successful" << std::endl;
    }

    // Make a request to mark a task as failed
    if (statuscope.Failure("vR6gsTgSDcsbENCpw", "No space left on device")) {
        std::cout << "\nRequest succeeded to mark a task as failed" << std::endl;
    }

    return 0;
}

