#include <CXX/Extensions.hxx>
#include <CXX/Objects.hxx>
#include <Python.h>

#include <list>

#include <string>
#include <queue>

#include "hashcore.h"

class SequenceHasher : public Py::PythonExtension<SequenceHasher> {
	public:
        SequenceHasher();
        ~SequenceHasher();

        //python methods
        Py::Object py_addReference(const Py::Tuple &args);
        Py::Object py_initialize(const Py::Tuple &args);
        Py::Object py_hash(const Py::Tuple &args);

        //pycxx methods
        static void init_type();
        virtual Py::Object repr();
        virtual Py::Object getattr( const char *name);
        Py::Object reference_count(const Py::Tuple& args){
            return Py::Int(this->ob_refcnt);
        }
    private:
        bool _initialized;
        std::list<ObservationSet*> _obs;
        ReferenceSet *_ref;
        std::list<LikelihoodSet*> _likelihoods;
}; 