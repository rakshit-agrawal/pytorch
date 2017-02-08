#include "TensorDescriptor.hpp"
#include "tensors/THTensor.hpp"

using namespace thd;

THDTensorDescriptor* THDTensorDescriptor_newFromTHDoubleTensor(THDoubleTensor *tensor) {
  THDoubleTensor_retain(tensor);
  return new THTensor<double>(tensor);
}

THDTensorDescriptor* THDTensorDescriptor_newFromTHFloatTensor(THFloatTensor *tensor) {
  THFloatTensor_retain(tensor);
  return new THTensor<float>(tensor);
}

THDTensorDescriptor* THDTensorDescriptor_newFromTHLongTensor(THLongTensor *tensor) {
  THLongTensor_retain(tensor);
  return new THTensor<long>(tensor);
}

THDTensorDescriptor* THDTensorDescriptor_newFromTHIntTensor(THIntTensor *tensor) {
  THIntTensor_retain(tensor);
  return new THTensor<int>(tensor);
}

THDTensorDescriptor* THDTensorDescriptor_newFromTHShortTensor(THShortTensor *tensor) {
  THShortTensor_retain(tensor);
  return new THTensor<short>(tensor);
}

THDTensorDescriptor* THDTensorDescriptor_newFromTHCharTensor(THCharTensor *tensor) {
  THCharTensor_retain(tensor);
  return new THTensor<char>(tensor);
}

THDTensorDescriptor* THDTensorDescriptor_newFromTHByteTensor(THByteTensor *tensor) {
  THByteTensor_retain(tensor);
  return new THTensor<unsigned char>(tensor);
}

THD_API void THDTensorDescriptor_free(THDTensorDescriptor* desc) {
  delete desc;
}
