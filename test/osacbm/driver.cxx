#include "StateDetection.hxx"
#include "DAReal.hxx"
#include "listOfDouble.hxx"
#include "DADataSeq.hxx"
#include "DADataEvent.hxx"
#include "DataEvent.hxx"
#include "DataStatus.hxx"
#include "NumAlert.hxx"
#include "SITE_CATEGORY.hxx"
#include "Site.hxx"
#include "MIMKey3.hxx"
#include "MIMKey1.hxx"
#include "OsacbmTime.hxx"
#include "OsacbmTimeType.hxx"
#include "RefUnit.hxx"
#include "UnitConverter.hxx"
#include "EngUnit.hxx"
#include "EnumValue.hxx"
#include "LocalTime.hxx"
#include "AlertRegionRef.hxx"

#include <iostream>
#include <assert.h>

#include "reflex.h"
#include "reflex/traits/xsd_traits.h"

namespace osacbm {

  void enum_cast(osacbm::DataStatus & dst, int src) {
    dst = osacbm::DataStatus::value(src);
  }

  void enum_cast(osacbm::SITE_CATEGORY & dst, int src) {
    dst = osacbm::SITE_CATEGORY::value(src);
  }

  void enum_cast(osacbm::OsacbmTimeType & dst, int src) {
    dst = osacbm::OsacbmTimeType::value(src);
  }

};

REFLEX_ADAPT_ENUM(
    osacbm::DataStatus,
    (OK,        0)
    (FAILED,    1)
    (UNKNOWN,   2)
    (NOT_USED,  3)
    );
 
REFLEX_ADAPT_ENUM(
    osacbm::SITE_CATEGORY,
    (SITE_ZERO,           0)
    (SITE_SPECIFIC,       1)
    (SITE_PLAT,           2)
    (SITE_TEMPLATE,       3)
    (SITE_ENT_ZERO,       4)
    (SITE_ZERO_ONE,       5)
    (SITE_ZERO_TWO,       6)
    (SITE_PLAT_TRNG_DATA, 7)
    );

REFLEX_ADAPT_ENUM(
    osacbm::OsacbmTimeType,
    (OSACBM_TIME_MIMOSA,       0)
    (OSACBM_TIME_POSIX_NSEC_8, 1)
    (OSACBM_TIME_POSIX_USEC_8, 2)
    (OSACBM_TIME_POSIX_USEC_6, 3)
    (OSACBM_TIME_POSIX_MSEC_6, 4)
    (OSACBM_TIME_POSIX_SEC_4,  5)
    (OSACBM_TIME_TICK_NSEC,    6)
    (OSACBM_TIME_TICK_USEC,    7)
    (OSACBM_TIME_TICK_MSEC,    8)
    (OSACBM_TIME_SYSTEM_TICK,  9) 
    );

REFLEX_ADAPT_STRUCT(
    osacbm::DAReal,
    (osacbm::DAReal::value_type, value())
    );

REFLEX_ADAPT_STRUCT(
    osacbm::Site,
    (osacbm::SITE_CATEGORY,                category())
    (osacbm::Site::regId_optional,         regId())
    (osacbm::Site::siteId_optional,        siteId())
    (osacbm::Site::systemUserTag_optional, systemUserTag())
    (osacbm::Site::userTag_optional,       userTag())
    );

REFLEX_ADAPT_STRUCT(
    osacbm::MIMKey3,
    (osacbm::MIMKey3::code_type,     code())
    (osacbm::MIMKey3::dbId_type,     dbId())
    (osacbm::MIMKey3::name_optional, name())
    (osacbm::Site,                   site())
    );

REFLEX_ADAPT_STRUCT(
    osacbm::MIMKey1,
    (xml_schema::unsigned_int,         code())
    (osacbm::MIMKey1::name_optional,   name())
    );

REFLEX_ADAPT_STRUCT(
    osacbm::LocalTime,
    (osacbm::LocalTime::dst_type,       dst())
    (osacbm::LocalTime::hourDelta_type, hourDelta())
    (osacbm::LocalTime::minDelta_type,  minDelta())
    );

REFLEX_ADAPT_STRUCT(
    osacbm::OsacbmTime,
    (osacbm::OsacbmTime::localTime_optional,   localTime())
    (osacbm::OsacbmTime::time_type,            time())
    (osacbm::OsacbmTime::time_binary_optional, time_binary())
    (osacbm::OsacbmTime::time_type_type,       time_type1())
    );

REFLEX_ADAPT_STRUCT(
    osacbm::RefUnit,
    (osacbm::MIMKey1, id())
    );

REFLEX_ADAPT_STRUCT(
    osacbm::UnitConverter,
    (xml_schema::double_, multiplier())
    (xml_schema::double_, offset())
    );

REFLEX_ADAPT_STRUCT(
    osacbm::EngUnit,
    (osacbm::EngUnit::abbrev_optional,   abbrev())
    (osacbm::EngUnit::code_type,         code())
    (osacbm::EngUnit::dbId_type,         dbId())
    (osacbm::EngUnit::name_optional,     name())
    (osacbm::EngUnit::refUnit_optional,  refUnit())
    (osacbm::Site,                       site())
    (osacbm::EngUnit::unitConv_optional, unitConv())
    );

REFLEX_ADAPT_STRUCT(
    osacbm::EnumValue,
    (osacbm::EnumValue::enumEU_optional, enumEU())
    (osacbm::EnumValue::name_optional,   name())
    (osacbm::EnumValue::value_type,      value())
    );

REFLEX_ADAPT_STRUCT(
    osacbm::NumAlert,
    (osacbm::NumAlert::alertName_optional,      alertName())
    (osacbm::NumAlert::alertSeverity_optional,  alertSeverity())
    (osacbm::NumAlert::alertTypeCode_type,      alertTypeCode())
    (osacbm::NumAlert::alertTypeId_optional,    alertTypeId())
    (osacbm::NumAlert::alertTypeSite_optional,  alertTypeSite())
    (osacbm::NumAlert::hiSideAlert_optional,    hiSideAlert())
    (osacbm::NumAlert::lastTrigger_optional,    lastTrigger())
    (osacbm::NumAlert::regionEnum_optional,     regionEnum())
    (osacbm::NumAlert::regionRef_optional,      regionRef())
    );

REFLEX_ADAPT_STRUCT(
    osacbm::AlertRegionRef,
    (xml_schema::unsigned_int,                          regionId())
    (osacbm::AlertRegionRef::regionLastUpdate_optional, regionLastUpdate())
    (osacbm::AlertRegionRef::regionSeq_optional,        regionSeq())
    (osacbm::AlertRegionRef::regionSite_optional,       regionSite())
    );

REFLEX_ADAPT_STRUCT(
    osacbm::DataEvent,
    (osacbm::DataEvent::alertStatus_optional,  alertStatus())
    (osacbm::DataEvent::confid_optional,       confid())
    (xml_schema::unsigned_int,                 id())
    (osacbm::DataEvent::sequenceNum_optional,  sequenceNum())
    (osacbm::DataEvent::site_optional,         site())
    (osacbm::DataEvent::time_optional,         time())
    );

REFLEX_ADAPT_VALUETYPE(
    osacbm::DADataEvent,
    osacbm::DataEvent,
    (osacbm::DADataEvent::dataStatus_optional, dataStatus())
    (osacbm::DADataEvent::numAlerts_sequence,  numAlerts())
    );

REFLEX_ADAPT_VALUETYPE(
    osacbm::DADataSeq, 
    osacbm::DADataEvent,
    (osacbm::DADataSeq::values_sequence,            values())
    (osacbm::DADataSeq::valuesList_optional,        valuesList())
    (osacbm::DADataSeq::valuesBinary_optional,      valuesBinary())
    (osacbm::DADataSeq::xAxisDeltas_sequence,       xAxisDeltas())
    (osacbm::DADataSeq::xAxisDeltasList_optional,   xAxisDeltasList())
    (osacbm::DADataSeq::xAxisDeltasBinary_optional, xAxisDeltasBinary())
    (osacbm::DADataSeq::xAxisStart_optional,        xAxisStart())
    );

template <class T>
void print_tc()
{
  reflex::SafeTypeCode<T> stc(reflex::make_typecode<T>());
  reflex::detail::print_IDL(stc.get(), 0);
}

void test_DADataSeq()
{
  osacbm::DADataSeq dataseq1;

  dataseq1.id() = 777;

  dataseq1.values().push_back(10);
  dataseq1.values().push_back(20);
  dataseq1.values().push_back(30);

  osacbm::listOfDouble list_double(10, 9.99);
  dataseq1.valuesList() = list_double;

  dataseq1.xAxisStart(99.99);

  reflex::TypeManager<osacbm::DADataSeq> tm_dataseq;

  reflex::SafeDynamicData<osacbm::DADataSeq> sdd1 = 
    tm_dataseq.create_dynamicdata(dataseq1);

  std::cout << dataseq1 << std::endl;
  // valuetype printing appears to have bugs
  sdd1.get()->print(stdout, 2);

  osacbm::DADataSeq dataseq2;

  reflex::read_dynamicdata(dataseq2, sdd1);

  reflex::SafeDynamicData<osacbm::DADataSeq> sdd2 = 
    tm_dataseq.create_dynamicdata(dataseq2);

  assert(dataseq1 == dataseq2);
  assert(sdd1.get()->equal(*sdd2.get()));
}

int main(void)
{
  print_tc<osacbm::DAReal>();
  print_tc<osacbm::DADataSeq>();

  test_DADataSeq();


  return 0;
}
