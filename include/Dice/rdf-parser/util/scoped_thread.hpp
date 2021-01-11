
#ifndef PEGTL_RDF_PARSER_SCOPED_THREAD_HPP
#define PEGTL_RDF_PARSER_SCOPED_THREAD_HPP

namespace rdf_parser {
	namespace util {

#include <thread>
#include <utility>

		class ScopedThread {
			std::thread t;

		public:
			explicit ScopedThread(std::thread t_) : t(std::move(t_)) {
				if (!t.joinable()) throw std::logic_error("No thread");
			}

			~ScopedThread() {
				t.join();
			}

			ScopedThread(ScopedThread &) = delete;

			ScopedThread &operator=(ScopedThread const &) = delete;
		};
	}// namespace util
}// namespace rdf_parser
#endif//PEGTL_RDF_PARSER_SCOPED_THREAD_HPP
