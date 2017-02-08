#ifndef TH_GENERIC_FILE
#define TH_GENERIC_FILE "generic/Tensor.h"
#else

struct THPTensor {
  PyObject_HEAD
  THTensor *cdata;
};

#ifndef THD_GENERIC_FILE
struct THSPTensor {
  PyObject_HEAD
  THSTensor *cdata;
};
#endif

/**
 * Creates a new Python (Sparse) Tensor object using the give THTensor. The
 * returned PyObject* pointer can be safely casted to a THPTensor*.  Note: This
 * "steals" the THTensor* `ptr`.  On error, NULL is returned and the `ptr` ref
 * count is decremented.
 */
THP_API PyObject * THPTensor_(New)(THTensor *ptr);
#ifndef THD_GENERIC_FILE
THP_API PyObject * THSPTensor_(New)(THSTensor *ptr);
#endif

/**
 * Creates a new empty Python Tensor object
 */
THP_API PyObject * THPTensor_(NewEmpty)(void);
#ifndef THD_GENERIC_FILE
THP_API PyObject * THSPTensor_(NewEmpty)(void);
#endif

extern PyObject *THPTensorClass;
#ifndef THD_GENERIC_FILE
extern PyObject *THSPTensorClass;
#endif

#ifdef _THP_CORE
#include "torch/csrc/Types.h"

// TODO: init stateless in THPTensor_(init) and remove this
extern PyTypeObject THPTensorStatelessType;
#ifndef THD_GENERIC_FILE
extern PyTypeObject THSPTensorStatelessType;
#endif
bool THPTensor_(init)(PyObject *module);
#ifndef THD_GENERIC_FILE
bool THSPTensor_(init)(PyObject *module);
#endif

extern PyTypeObject THPTensorType;
template <> struct THPTypeInfo<THTensor> {
  static PyTypeObject* pyType() { return &THPTensorType; }
  static THTensor* cdata(PyObject* p) { return ((THPTensor*)p)->cdata; }
};
#endif

#endif
