#ifndef RDF_PARSER_CONFIG_HPP
#define RDF_PARSER_CONFIG_HPP

namespace Dice::rdf_parser::internal::Turtle::Configurations {
	constexpr std::size_t RdfConcurrentStreamParser_BufferSize = 1024 * 1024 * 128;
	constexpr std::size_t RdfConcurrentStreamParser_QueueCapacity = 100'000;
}// namespace Dice::rdf_parser::internal::Turtle::Configurations

#endif//RDF_PARSER_CONFIG_HPP
