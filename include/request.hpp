#pragma once
#include <string>
#include <map>
#include <sstream>
#include <utility>
#include <vector>
#include <fstream>
#include <cinttypes>
#ifdef MANUAL_CURL_PATH // manually linking
#include MANUAL_CURL_PATH
#else
#include <curl/curl.h>
#include <functional>

#endif

typedef std::map<std::string, std::string> headers_t;
typedef headers_t cookies_t;

struct Response
{
    CURLcode curlCode;
    int code;
    std::string message;
    std::string data;
    std::vector<uint8_t> rawData;
    std::vector<uint8_t> rawHeaders;
    headers_t headers;
    cookies_t cookies;
};

class Form {
public:
    explicit Form(CURL* curl) {
        form = curl_mime_init(curl);
    };

    /**
     * @brief append a string to the form
     * @param name the name of the field
     * @param value the value of the field
    */
    void append_string(const std::string& name, const std::string& value) {
        auto part = append(name);
        curl_mime_data(part, value.c_str(), value.size());
    }

    /**
     * @brief append a file to the form
     * @param name the name of the field
     * @param path the path of the file
    */
    void append_file(const std::string& name, const std::string& path) {
        auto part = append(name);
        curl_mime_filedata(part, path.c_str());
    }

    /**
     * @brief append a file to the form
     * @param name the name of the field
     * @param path the path of the file
     * @param filename the filename of the file
    */
    void append_file(const std::string& name, const std::string& path, const std::string& filename) {
        auto part = append(name);
        curl_mime_filename(part, filename.c_str());
        curl_mime_filedata(part, path.c_str());
    }

    /**
     * @brief append a part to the form
     * @param name the name of the field
     * @return the part
     * @note you can use this to set custom field data
    */
    curl_mimepart* append(const std::string& name) {
        auto part = curl_mime_addpart(form);
        curl_mime_name(part, name.c_str());
        return part;
    }

    curl_mime* get() {
        return form;
    }

protected:
    friend class Request;
    curl_mime* form = nullptr;
};

class Request
{

public:
    explicit Request(std::string url) : m_url(std::move(url)), m_headers() {}

    Request(std::string url, std::string data) : m_url(std::move(url)), m_data(std::move(data)), m_headers() {}

    Request(std::string url, std::string data, headers_t headers) : m_url(std::move(url)), m_data(std::move(data)), m_headers(std::move(headers)) {}

    ~Request()
    {
        if (m_curl_headers)
            curl_slist_free_all(m_curl_headers);
        if (m_mime)
            curl_mime_free(m_mime);
        if (m_curl)
            curl_easy_cleanup(m_curl);
    }

    /**
     * @brief initalize the curl backend, must be called before any other method
     * @return true when success
     */
    int initalize()
    {
        CURL* localCurl = curl_easy_init();
        this->m_curl = localCurl;
        return this->m_curl != nullptr;
    }
    /**
     * @brief execute the request with the method POST
     * @return the response of the request
     */
    Response post()
    {
        this->prepare();
        curl_easy_setopt(m_curl, CURLOPT_POST, 1);
        return this->execute();
    }
    /**
     * @brief execute the request with the method GET
     * @return the response of the request
     */
    Response get()
    {
        this->prepare();
        curl_easy_setopt(m_curl, CURLOPT_HTTPGET, 1);
        return this->execute();
    }
    /**
     * @brief execute the request with the method defined (must be a valid HTTP 1.1 method)
     * @param method the method to use
     * @return the response of the request
     */
    Response request(const std::string& method)
    {
        this->prepare();
        curl_easy_setopt(m_curl, CURLOPT_CUSTOMREQUEST, method.c_str());
        return this->execute();
    }
    /**
    * @brief Download a file from the specified URL using a GET request and save it to the given file path
    * @param file_path The path where the downloaded file should be saved
    * @return The result of the cURL request
    */
    int download_file(const std::string& file_path)
    {
        std::ofstream ofs(file_path, std::ios::out | std::ios::binary);

        this->prepare();

        curl_easy_setopt(m_curl, CURLOPT_HTTPGET, 1L);
        curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, _m_fileWriteFunction);
        curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, &ofs);
        curl_easy_setopt(m_curl, CURLOPT_FAILONERROR, 1L);

        int result = curl_easy_perform(m_curl);

        ofs.close();

        return result;
    }
    /**
     * @brief prepare new form data
     * @return the form data
    */
    Form form_data() {
        return Form(m_curl);
    }
    /**
     * @brief execute a multipart/form-data request
     * @param form the form data
     * @return the response of the request
    */
    Response form(Form& form) {
        this->m_headers["Content-Type"] = "multipart/form-data";
        this->prepare();
        curl_easy_setopt(m_curl, CURLOPT_MIMEPOST, form.get());
        if (this->m_mime) curl_mime_free(m_mime);
        this->m_mime = form.form;
        return this->execute();
    }
    /**
     * @brief set the url of the request
     * @param url the url of the request
     */
    void set_url(const std::string& url)
    {
        this->m_url = url;
    }
    /**
     * @brief set the data of the request
     * @param data the data of the request
     */
    void set_data(const std::string& data)
    {
        this->m_data = data;
    }
    /**
     * @brief set a header in the request
     * @param key the key of the header
     * @param value the value of the header
     */
    void set_header(const std::string& key, const std::string& value)
    {
        this->m_headers[key] = value;
    }
    /**
     * @brief set a cookie in the request
     * @param key the key of the cookie
     * @param value the value of the cookie
     */
    void set_cookie(const std::string& key, const std::string& value)
    {
        this->m_cookies[key] = value;
    }
    /**
     * @brief remove a header from the request
     * @param key the key of the header
     */
    void remove_header(const std::string& key)
    {
        this->m_headers.erase(key);
    }
    /**
     * @brief remove a cookie from the request
     * @param key the key of the cookie
     */
    void remove_cookie(const std::string& key)
    {
        this->m_cookies.erase(key);
    }
    /**
     * @brief return a modifiable map of the headers of the request
     * @return the map of the headers
     */
    const headers_t& get_headers() const
    {
        return m_headers;
    }
    /**
     * @brief return a modifiable map of the cookies of the request
     * @return the map of the cookies
     */
    const cookies_t& get_cookies() const
    {
        return m_cookies;
    }
    /**
     * @brief return the url of the request
     * @return the url
     */
    std::string get_url() const
    {
        return m_url;
    }
    /**
     * @brief return the data of the request
     * @return the data
     */
    std::string get_data() const
    {
        return m_data;
    }

private:

    static size_t _m_writeFunction(void* ptr, size_t size, size_t nmemb, std::vector<uint8_t>* userdata)
    {
        auto* data = (uint8_t*)ptr;
        for (size_t i = 0; i < nmemb; i++)
        {
            userdata->push_back(data[i]);
        }

        return size * nmemb;
    }

    static size_t _m_fileWriteFunction(void* ptr, size_t size, size_t nmemb, void* userdata)
    {
        auto* ofs = static_cast<std::ofstream*>(userdata);
        size_t bytes_written = size * nmemb;
        ofs->write(static_cast<const char*>(ptr), bytes_written);
        return bytes_written;
    }

    std::string m_url;
    std::string m_data;
    headers_t m_headers{};
    cookies_t m_cookies{};
    curl_slist* m_curl_headers = nullptr;

    void prepare()
    {
#ifdef _VERBOSE
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
#endif
        curl_easy_setopt(m_curl, CURLOPT_URL, m_url.c_str());
        // set headers
        prepareHeaders();
        if (!m_data.empty()) {
            curl_easy_setopt(m_curl, CURLOPT_POSTFIELDSIZE, m_data.size());
            curl_easy_setopt(m_curl, CURLOPT_POSTFIELDS, m_data.c_str());
        }
    }
    void prepareHeaders()
    {
        // cleanup old headers in case this gets reused
        if (m_curl_headers)
            curl_slist_free_all(m_curl_headers);
        // redefine headers
        curl_slist* curl_headers = nullptr;
        for (auto [key, value] : m_headers)
        {
            std::string header = key + ": " + value;
            curl_headers = curl_slist_append(curl_headers, header.c_str());
        }

        // prepare cookies
        if (!m_cookies.empty()) {
            std::string cookie_header = "Cookie: ";
            for (auto [key, value] : m_cookies) {
                cookie_header += key + "=" + value + "; ";
            }
            curl_headers = curl_slist_append(curl_headers, cookie_header.c_str());
        }

        this->m_curl_headers = curl_headers; // save for later cleanup
        // set headers
        curl_easy_setopt(m_curl, CURLOPT_HTTPHEADER, curl_headers);
    }

    Response execute()
    {
        Response response{};
        std::vector<uint8_t> responseData;
        std::vector<uint8_t> headerData;
        curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, _m_writeFunction);
        curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, &responseData);
        curl_easy_setopt(m_curl, CURLOPT_HEADERDATA, &headerData);

        CURLcode curlCode = curl_easy_perform(m_curl);

        // read into response data
        response.rawData = responseData;
        uint8_t* rawData = responseData.data();
        response.data = std::string(rawData, rawData + responseData.size());
        response.rawHeaders = headerData;
        uint8_t* rawHeaders = headerData.data();
        std::string headers = std::string(rawHeaders, rawHeaders + headerData.size());

        // get first line
        std::stringstream ss(headers);
        std::string line;
        std::getline(ss, line);

        size_t index = line.find(' ');
        std::string responsePart = line.substr(index + 1);

        index = responsePart.find(' ');
        std::string message = responsePart.substr(index + 1);
        std::string codeStr = responsePart.substr(0, index);

        int code = std::stoi(codeStr);

        response.code = code;
        response.message = message;

        // parse header string to vector of headers
        ss = std::stringstream(headers);
        while (std::getline(ss, line))
        {
            std::string key;
            std::string value;
            std::stringstream lineStream(line);
            std::getline(lineStream, key, ':');
            // consume 1 space
            std::getline(lineStream, value, ' ');
            // get actual value
            std::getline(lineStream, value, '\r');

            response.headers[key] = value;
        }

        if (response.headers.find("set-cookies") != response.headers.end()) {
            // parse response cookies
            std::stringstream ss(response.headers["set-cookies"]);
            std::string line;
            while (std::getline(ss, line))
            {
                std::string key;
                std::string value;
                std::stringstream lineStream(line);
                std::getline(lineStream, key, '=');
                // get actual value
                std::getline(lineStream, value, ';');

                response.cookies[key] = value;
            }
        }
        response.curlCode = curlCode;
        return response;
    }

    CURLcode rawExecute()
    {
        return curl_easy_perform(m_curl);
    }

    friend class WebSocket;

    CURL* m_curl{ nullptr };
    curl_mime* m_mime{ nullptr };
};

/**
 * @brief A class to handle websocket connections
 *
 * note: in current curl version (7.88.1) curl must be compiled with the --enable-websockets flag
 * or `set(ENABLED_WEBSOCKETS ON)` in cmake
 */
class WebSocket {

public:

    explicit WebSocket(Request& request) : m_request(request) {}

    /**
     * Initialize the websocket connection
     *
     * note: this must be called before any other function
     */
    void initialize() {
        m_request.initalize();
        curl_easy_setopt(m_request.m_curl, CURLOPT_WRITEFUNCTION, _m_websocket_writeFunction);
        curl_easy_setopt(m_request.m_curl, CURLOPT_WRITEDATA, this);
        curl_easy_setopt(m_request.m_curl, CURLOPT_CLOSESOCKETFUNCTION, _m_websocket_closeFunction);
        curl_easy_setopt(m_request.m_curl, CURLOPT_CLOSESOCKETDATA, this);

    }

    /**
     * @brief Creates the websocket connection, this will block until the connection is disconnected
     */
    void connect() {
        m_request.prepare();
        // run this in a thread
        m_request.rawExecute();
    }

    /**
     * @brief Sends data to the websocket
     * @param data data to send
     * @param type type of data to send, either CURLWS_TEXT, CURLWS_BINARY or CURLWS_CLOSE (default: CURLWS_TEXT)
     */
    void send(const std::string& data, int type = CURLWS_TEXT) {
        size_t sent = 0;
        int code = curl_ws_send(m_request.m_curl, data.c_str(), data.size(), &sent, 0, type);
        if (code != CURLcode::CURLE_OK) {
            throw std::runtime_error("Failed to send data " + std::string(curl_easy_strerror((CURLcode)code)));
        }
        if (sent != data.size()) {
            throw std::runtime_error("Failed to send all data");
        }
    }

    /**
     * @brief Disconnects the websocket
     */
    void disconnect() {
        send("", CURLWS_CLOSE);
        this->m_should_close = true;
    }

    /**
     * @brief Sets the message handler
     */
    void setOnMessage(const std::function<void(WebSocket*, const std::string&)>& function) {
        this->m_on_message = function;
    }

    /**
     * @brief Sets the close handler
     */
    void setOnClose(std::function<void(WebSocket*)> function) {
        this->m_on_close = std::move(function);
    }

    /**
     * @returns whether the websocket is connected
     */
    [[nodiscard]] bool isConnected() const {
        return m_connected;
    }

private:
    static size_t _m_websocket_writeFunction(void* ptr, size_t size, size_t nmemb, void* userdata) {
        auto ws = (WebSocket*)userdata;
        if (ws->m_should_close) {
            return 0;
        }
        if (!ws->m_connected) ws->m_connected = true;
        ws->m_buffer.insert(ws->m_buffer.end(), (uint8_t*)ptr, (uint8_t*)ptr + size * nmemb);
        auto meta = curl_ws_meta(ws->m_request.m_curl);
        if (meta && meta->bytesleft != 0) {
            return size * nmemb;
        }
        else {
            ws->m_on_message(ws, std::string(ws->m_buffer.begin(), ws->m_buffer.end()));
            ws->m_buffer.clear();
            return size * nmemb;
        }
    }

    static int _m_websocket_closeFunction(void* clientp, curl_socket_t item) {
        auto ws = (WebSocket*)clientp;
        ws->m_connected = false;
        ws->m_on_close(ws);
        return 0;
    }

    Request& m_request;
    // Events
    std::function<void(WebSocket*, std::string)> m_on_message;
    std::function<void(WebSocket*)> m_on_close;
    // Buffer
    std::vector<uint8_t> m_buffer;
    // State
    bool m_connected{ true };
    bool m_should_close{ false };

};