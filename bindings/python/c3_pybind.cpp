#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "../../core/context/context.h"
#include "../../core/recall/recall.h"
#include "../../core/memory/memory.h"

namespace py = pybind11;
using namespace c3;

PYBIND11_MODULE(c3, m)
{
    m.doc() = "C3 Causal Memory Core";

    /* ---------------- Enums ---------------- */

    py::enum_<Intent>(m, "Intent")
        .value("UNKNOWN", INTENT_UNKNOWN)
        .value("FACTUAL", INTENT_FACTUAL)
        .value("INSTRUCTIONAL", INTENT_INSTRUCTIONAL)
        .value("EXPLANATORY", INTENT_EXPLANATORY)
        .value("CONVERSATIONAL", INTENT_CONVERSATIONAL)
        .value("DEBUGGING", INTENT_DEBUGGING);

    py::enum_<Domain>(m, "Domain")
        .value("GENERAL", DOMAIN_GENERAL)
        .value("SEARCH", DOMAIN_SEARCH)
        .value("QA", DOMAIN_QA)
        .value("CHAT", DOMAIN_CHAT)
        .value("CODE", DOMAIN_CODE)
        .value("AGENT", DOMAIN_AGENT);

    py::enum_<Tool>(m, "Tool")
        .value("NONE", TOOL_NONE)
        .value("SEARCH", TOOL_SEARCH)
        .value("RAG", TOOL_RAG)
        .value("API", TOOL_API)
        .value("CODE_EXEC", TOOL_CODE_EXEC)
        .value("AGENT", TOOL_AGENT);

    /* ---------------- Context ---------------- */

    py::class_<ContextFeatures>(m, "Context")
        .def(py::init<>())
        .def_readwrite("intent", &ContextFeatures::intent)
        .def_readwrite("domain", &ContextFeatures::domain)
        .def_readwrite("tool", &ContextFeatures::tool)
        .def_readwrite("retry", &ContextFeatures::retry);

    /* ---------------- Bias ---------------- */

    py::class_<Bias>(m, "Bias")
        .def_readonly("prefer", &Bias::prefer)
        .def_readonly("avoid", &Bias::avoid);

    /* ---------------- Memory ---------------- */

    py::class_<Memory>(m, "Memory")
        .def(py::init<>())
        .def("recall", &Memory::recall,
             py::arg("context"),
             "Recall bias for a context")
        .def("update", &Memory::update,
             py::arg("context"),
             py::arg("action"),
             py::arg("outcome"),
             py::arg("now"),
             "Update memory with outcome")
        .def("num_contexts", &Memory::num_contexts)
        .def("clear", &Memory::clear);
}
