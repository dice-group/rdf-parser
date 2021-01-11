//
// Created by fakhr on 11.01.21.
//

#ifndef RDF_PARSER_CONFIG_HPP
#define RDF_PARSER_CONFIG_HPP

namespace rdf_parser::Turtle::Configurations {
	const std::size_t RdfConcurrentStreamParser_BufferSize = 1024 * 1024;
	const std::size_t RdfConcurrentStreamParser_QueueCapacity = 100000;
	const std::size_t RdfStreamParser_BufferSize = 10000000;
}// namespace rdf_parser::Turtle::Configurations

#endif//RDF_PARSER_CONFIG_HPP
