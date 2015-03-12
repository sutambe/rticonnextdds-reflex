/*********************************************************************************************
(c) 2005-2014 Copyright, Real-Time Innovations, Inc.  All rights reserved.
RTI grants Licensee a license to use, modify, compile, and create derivative works
of the Software.  Licensee has the right to distribute object form only for use with RTI
products.  The Software is provided "as is", with no warranty of any type, including
any warranty for fitness for any purpose. RTI is under no obligation to maintain or
support the Software.  RTI shall not be liable for any incidental or consequential
damages arising out of the use or inability to use the software.
**********************************************************************************************/

#ifndef RTIREFLEX_REFLEX_FWD_H
#define RTIREFLEX_REFLEX_FWD_H

struct DDS_DynamicData;

namespace reflex {

  class AutoDynamicData; // See auto_dd.h

  template <class T>
  class SafeDynamicData; // See reflex.h 

  template <class T, class>
  class SafeTypeCode;   // See safe_typecode.h

  /**
  * Creates a <a href="http://community.rti.com/rti-doc/510/ndds.5.1.0/doc/html/api_cpp/structDDS__TypeCode.html">TypeCode</a>
  * for structured type T.
  * @param name Optional name for the top-level struct type.
  *        If none is provided, the unqualified name of type T is used.
  * @return The TypeCode for type T wrapped in a SafeTypeCode object.
  * @pre    Type T must be adapted using the RTI_ADAPT_STURCT macro.
  */
  template <class T>
  SafeTypeCode<T> make_typecode(const char * name = 0);

  /**
   * Populates the <a href="http://community.rti.com/rti-doc/510/ndds.5.1.0/doc/html/api_cpp/structDDS__DynamicData.html">
   * DDS_DynamicData</a> instance from the source data.
   * @param src The source object
   * @param dest The DDS_DynamicData instance that will be populated
   * @return Nothing
   * @see reflex::make_typecode
   * @pre The TypeCode for the DDS_DynamicData instance must be generated by reflex::make_typecode.
   */
  template <class T>
  void fill_dd(const T & src, DDS_DynamicData &dest);

  /**
  * Copies data into the underlying a <a href="http://community.rti.com/rti-doc/510/ndds.5.1.0/doc/html/api_cpp/structDDS__DynamicData.html">
  * DDS_DynamicData</a> instance.
  * @param src The source object
  * @param dest The instance that will be populated
  * @return Nothing
  * @pre The TypeCode for the underlying DDS_DynamicData instance must be generated by reflex::make_typecode.
  */
  template <class T>
  void fill_dd(const T & src, AutoDynamicData &dest);

  /**
   * Creates an type-safe, exception-safe instance of SafeDynamicData from a source object. 
   * This function combines reflex::make_typecode and reflex::fill_dd into one.
   * @param src The source object of type T
   * @return Type-safe, exception-safe instance of SafeDynamicData 
   * @see reflex::make_typecode
   * @see reflex::fill_dd
   * @pre Type T must be adapted using the RTI_ADAPT_STURCT macro.
   */
  template <class T>
  SafeDynamicData<T> make_dd(const T & src);

  /**
   * Extracts data out from a DDS_DynamicData instance and copies into an object of type T.
   * @param src The source DDS_DynamicData.
   * @param dest The destination object of type T.
   * @see reflex::fill_dd
   * @pre Type T must be adapted using the RTI_ADAPT_STURCT macro.
   */
  template <class T>
  void extract_dd(const DDS_DynamicData & src, T & dest);

  /**
  * Extracts data out from a AutoDynamicData instance and copies into an object of type T.
  * @param src The source DDS_DynamicData.
  * @param dest The destination object of type T.
  * @see reflex::fill_dd
  * @pre Type T must be adapted using the RTI_ADAPT_STURCT macro.
  */
  template <class T>
  void extract_dd(const AutoDynamicData & src, T & dest);


}



#endif // RTIREFLEX_REFLEX_FWD_H
