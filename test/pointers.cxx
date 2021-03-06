/*********************************************************************************************
(c) 2005-2014 Copyright, Real-Time Innovations, Inc.  All rights reserved.
RTI grants Licensee a license to use, modify, compile, and create derivative works
of the Software.  Licensee has the right to distribute object form only for use with RTI
products.  The Software is provided "as is", with no warranty of any type, including
any warranty for fitness for any purpose. RTI is under no obligation to maintain or
support the Software.  RTI shall not be liable for any incidental or consequential
damages arising out of the use or inability to use the software.
**********************************************************************************************/

#include "pointers.h"
#include <memory>

#ifndef RTI_WIN32
namespace std {

  template <class T, class... Args>
  std::unique_ptr<T> make_unique(Args&&... args)
  {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
  }

}
#endif // RTI_WIN32


bool operator == (const pointers & lhs, const pointers & rhs)
{
  bool opt_same = true;
  
  if (lhs.optional_shared_ptr && rhs.optional_shared_ptr)
    opt_same = (*lhs.optional_shared_ptr == *rhs.optional_shared_ptr);
  else if(!lhs.optional_shared_ptr && !rhs.optional_shared_ptr)
    opt_same = true;
  else
    opt_same = false;

  return opt_same 
      && (*lhs.int_ptr == *rhs.int_ptr)
      && (*lhs.string_shared_ptr == *rhs.string_shared_ptr)
      && (*lhs.unique_ptr == *rhs.unique_ptr);
}

void write_pointers(int)
{
  reflex::SafeTypeCode<pointers>
    stc(reflex::make_typecode<pointers>());

  reflex::detail::print_IDL(stc.get(), 0);

  DDS_DynamicDataTypeProperty_t props;

  std::shared_ptr<DDSDynamicDataTypeSupport>
    safe_typeSupport(new DDSDynamicDataTypeSupport(stc.get(), props));

  reflex::AutoDynamicData d1(safe_typeSupport.get());
  reflex::AutoDynamicData d2(safe_typeSupport.get());

  pointers x;
  x.int_ptr = new int(12);
  //x.optional_shared_ptr = std::make_shared<int>(22);
  x.string_shared_ptr = std::make_shared<std::string>();
  x.unique_ptr = std::make_unique<int>(32);

  pointers y;
  y.int_ptr = new int();
  //y.optional_shared_ptr = std::make_shared<int>();
  y.string_shared_ptr = std::make_shared<std::string>();
  y.unique_ptr = std::make_unique<int>();

  reflex::write_dynamicdata(d1, x);
  reflex::read_dynamicdata(y, d1);
  std::cout << "pointers are same = " << std::boolalpha << (x == y) << "\n";

  //d1.get()->print(stdout, 2);

  delete x.int_ptr;
  delete y.int_ptr;
}

