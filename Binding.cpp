#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>
// Object includes 

#include "headers/Page.hpp"
#include "sources/Index.cpp"
#include "headers/IndexCache.hpp"




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
	.def(py::init<const std::string &, const std::unordered_map<std::string, std::string> &, const RubenSystems::Math::Matrix &>())
	.def("data", &idx::Page::data);

	//Bindings for IndexConfig
	py::class_<idx::IndexConfig>(m, "IndexConfig")
	.def(py::init<const std::string &, int, const std::vector<std::string> &, const std::tuple<int,int,int> &>());


	//Bindings for Index
	py::class_<idx::Index<idx::Page>>(m, "Index")
	.def(py::init<const idx::IndexConfig &>())
	.def("getItem", &idx::Index<idx::Page>::getItem)
	.def("add", &idx::Index<idx::Page>::add)
	.def("update", &idx::Index<idx::Page>::update)
	.def("remove", &idx::Index<idx::Page>::remove)
	.def("getSimilar", &idx::Index<idx::Page>::getSimilar)
	.def("getWhere", &idx::Index<idx::Page>::getWhere)
	.def("unarchive", &idx::Index<idx::Page>::unarchive)
	.def("archive", &idx::Index<idx::Page>::archive);


	py::class_<idx::IndexCache<idx::Page>>(m, "IndexCache")
	.def(py::init<>())
	// .def("__setitem__", &idx::IndexCache<idx::Page>::operator[])
	// .def("__getitem__", &idx::IndexCache<idx::Page>::operator[]);
	.def("__getitem__", &idx::IndexCache<idx::Page>::get)
	.def("remove", &idx::IndexCache<idx::Page>::remove)
	.def("__setitem__", &idx::IndexCache<idx::Page>::add);
}







