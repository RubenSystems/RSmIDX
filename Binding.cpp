#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
// Object includes 

#include "headers/Page.hpp"
#include "sources/Index.cpp"




namespace idx = RubenSystems::RSmIDX;
namespace py = pybind11;

PYBIND11_MODULE(rsmidx, m) {

	//Bindings for IndexData
	py::class_<idx::IndexData>(m, "IndexData")
	.def(py::init<>())
	.def_readwrite("uid", &idx::IndexData::uid)
	.def_readwrite("metadata", &idx::IndexData::metadata)
	.def_readwrite("matrix", &idx::IndexData::matrix);

	//Bindings for Page
	py::class_<idx::Page>(m, "Page")
	.def(py::init<const std::string &, const std::unordered_map<std::string, std::string> &, const RubenSystems::Math::Matrix &>());

	//Bindings for IndexConfig
	py::class_<idx::IndexConfig>(m, "IndexConfig")
	.def(py::init<const std::string &, int, const std::vector<std::string> &, const std::tuple<int,int,int> &>());


	//Bindings for Index
	py::class_<idx::Index<idx::Page>>(m, "Index")
	.def(py::init<const idx::IndexConfig &>())
	.def("getItem", &idx::Index<idx::Page>::getItem)
	.def("remove", &idx::Index<idx::Page>::remove)
	.def("getRelated", &idx::Index<idx::Page>::getRelated)
	.def("getWhere", &idx::Index<idx::Page>::getWhere)
	.def("unarchive", &idx::Index<idx::Page>::unarchive)
	.def("archive", &idx::Index<idx::Page>::archive);

}