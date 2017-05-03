#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <locale.h>

int main(int argc, char* argv[])
{
	using namespace web::http;
	std::locale::global(std::locale("Japanese_Japan.932"));
	setlocale(LC_ALL, std::locale().c_str());
	client::http_client c1(U("http://www.example.com"));

	uri_builder url1(U("redmine/projects/<project_name>/issues"));
	url1.append_query(U("format"), U("json"))
		.append_query(U("name"), U("<your_username>"))
		.append_query(U("key"), U("<your_api_key>"));

	pplx::task<http_response> t1{ c1.request(methods::GET, url1.to_string()) };

	try {
		t1.then([](http_response res) {
			std::wstring s1{ res.extract_string().get().c_str() };
			wprintf(s1.c_str());
		}).wait();
	} catch (const std::exception &e) {
		printf("Error exception:%s\n", e.what());
	}

	return 0;
}
