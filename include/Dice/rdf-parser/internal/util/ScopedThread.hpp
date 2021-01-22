#ifndef PEGTL_RDF_PARSER_SCOPED_THREAD_HPP
#define PEGTL_RDF_PARSER_SCOPED_THREAD_HPP

#include <thread>
#include <utility>

namespace Dice::rdf_parser::internal::util {

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
}// namespace Dice::rdf_parser::util
#endif//PEGTL_RDF_PARSER_SCOPED_THREAD_HPP
