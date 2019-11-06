#ifndef SPEC_UTILS_JS_H
#define SPEC_UTILS_JS_H

#include <memory>

#include <napi.h>

// Forward declarations
class SpecFile;
class Measurement;
class MeasurementInfo;



/** SpecFile cooresponds to the C++ Measurement class, which holds the
 information of a gamma spectrum from a single detection element.  If there is
 a neutron detector associated with the gamma detector, its counts are also
 in this class.
 */
class SpecRecord : public Napi::ObjectWrap<SpecRecord>
{
public:
  static void Init(Napi::Env &env, Napi::Object &exports);
  
  SpecRecord() = delete;
  
  SpecRecord( const Napi::CallbackInfo& info );
  
  static Napi::FunctionReference constructor;
  
  Napi::Value live_time(const Napi::CallbackInfo& info);
  Napi::Value real_time(const Napi::CallbackInfo& info);
  
  /*
  inline bool contained_neutron() const;
  inline int sample_number() const;
  inline const std::string &title() const;
  inline OccupancyStatus occupied() const;
  inline double gamma_count_sum() const;
  inline double neutron_counts_sum() const;
  inline float speed() const;
  inline double latitude() const;
  inline double longitude() const;
  inline bool has_gps_info() const;
  static bool valid_longitude( const double longitude );
  static bool valid_latitude( const double latitude );
  inline const boost::posix_time::ptime &position_time() const;
  inline const std::string &detector_name() const;
  inline int detector_number() const;
  inline const std::string &detector_type() const;
  inline QualityStatus quality_status() const;
  inline SourceType source_type() const;
  inline EquationType energy_calibration_model() const;
  inline const std::vector<std::string> &remarks() const;
  inline const boost::posix_time::ptime &start_time() const;
  inline const boost::posix_time::ptime start_time_copy() const;
  inline const std::vector<float> &calibration_coeffs() const;
  inline const DeviationPairVec &deviation_pairs() const;
  inline const std::shared_ptr< const std::vector<float> > &channel_energies() const;
  inline const std::shared_ptr< const std::vector<float> > &gamma_counts() const;
  inline const std::vector<float> &neutron_counts() const;
  inline size_t num_gamma_channels() const;
  inline size_t find_gamma_channel( const float energy ) const;
  inline float gamma_channel_content( const size_t channel ) const;
  inline float gamma_channel_lower( const size_t channel ) const;
  inline float gamma_channel_center( const size_t channel ) const;
  inline float gamma_channel_upper( const size_t channel ) const;
  inline float gamma_channel_width( const size_t channel ) const;
  double gamma_integral( float lower_energy, float upper_energy ) const;
  double gamma_channels_sum( size_t startbin, size_t endbin ) const;
  inline const std::shared_ptr< const std::vector<float> > & gamma_channel_energies() const;
  inline const std::shared_ptr< const std::vector<float> > &gamma_channel_contents() const;
  inline float gamma_energy_min() const;
  inline float gamma_energy_max() const;
  */
  
  
  
protected:
  std::shared_ptr<const Measurement> m_meas;
  
  friend class SpecFile;
};//class SpecRecord


/** SpecFile cooresponds to the C++ MeasurementInfo class, which basically
 represents a spectrum file.
 */
class SpecFile : public Napi::ObjectWrap<SpecFile>
{
  public:
  static Napi::Object Init( Napi::Env env, Napi::Object exports );
  
  
  SpecFile(const Napi::CallbackInfo& info);
  
  private:
  static Napi::FunctionReference constructor;
  
  Napi::Value gamma_live_time(const Napi::CallbackInfo& info);
  Napi::Value gamma_real_time(const Napi::CallbackInfo& info);
  Napi::Value gamma_count_sum(const Napi::CallbackInfo& info);
  Napi::Value contained_neutrons(const Napi::CallbackInfo& info);
  Napi::Value neutron_counts_sum(const Napi::CallbackInfo& info);
  
  Napi::Value num_gamma_channels(const Napi::CallbackInfo& info);
  Napi::Value num_spec_records(const Napi::CallbackInfo& info);

  
  /**
   "Unknown", "GR135", "IdentiFINDER", "IdentiFINDER-NG", "IdentiFINDER-LaBr3", "Detective", "Detective-EX", "Detective-EX100", "Detective-EX200", "Detective X", "SAIC8", "Falcon 5000", "MicroDetective", "MicroRaider", "SAM940", "SAM940LaBr3", "SAM945", "SRPM-210", "RS-701", "RS-705", "RadHunterNaI", "RadHunterLaBr3", "RSI-Unspecified", "RadEagle NaI 3x1", "RadEagle CeBr3 2x1", "RadEagle CeBr3 3x0.8", "RadEagle LaBr3 2x1";
   
   ToDo: make C++ DetectorType a JS enum, and also equiv for detectorTypeToString( const DetectorType type );
  */
  Napi::Value inferred_instrument_model(const Napi::CallbackInfo& info);
  
  
  /**
   PortalMonitor, SpecPortal, RadionuclideIdentifier,
   PersonalRadiationDetector, SurveyMeter, Spectrometer, Other
   */
  Napi::Value instrument_type(const Napi::CallbackInfo& info);
  
  /**
   */
  Napi::Value manufacturer(const Napi::CallbackInfo& info);
  
  /**
   */
  Napi::Value instrument_model(const Napi::CallbackInfo& info);
  
  Napi::Value instrument_id(const Napi::CallbackInfo& info);
  
  Napi::Value serial_number(const Napi::CallbackInfo& info);
  
  
  Napi::Value uuid(const Napi::CallbackInfo& info);
  
  Napi::Value passthrough(const Napi::CallbackInfo& info);
  Napi::Value filename(const Napi::CallbackInfo& info);
  Napi::Value remarks(const Napi::CallbackInfo& info);
  Napi::Value detector_names(const Napi::CallbackInfo& info);
  
  Napi::Value measurements(const Napi::CallbackInfo& info);
  
  Napi::Value has_gps_info(const Napi::CallbackInfo& info);
  Napi::Value mean_latitude(const Napi::CallbackInfo& info);
  Napi::Value mean_longitude(const Napi::CallbackInfo& info);
  
  /* Takes two arguments.
       First is a string giving the path to save to.
       Second is string giving format to save to, must be one of following:
         "TXT", "CSV", "PCF", "N42-2006", N42-2012", "CHN", "SPC-int",
         "SPC" (or equiv "SPC-float"), "SPC-ascii", "GR130v0", "GR135v2",
         "SPE" (or equiv "IAEA"), "HTML".
   
   ToDo: specify file format as an enum
   ToDo: Add additional argument to allow filtering which measurements get saved....
   */
  Napi::Value write_to_file(const Napi::CallbackInfo& info);
  
  /*
  inline const std::vector<int> &detector_numbers() const;
  inline const std::vector<std::string> &neutron_detector_names() const;
  inline const std::vector<std::string> &remarks() const;
  inline int lane_number() const;
  inline const std::string &measurement_location_name() const;
  inline const std::string &inspection() const;
  inline const std::string &measurment_operator() const;
  inline const std::set<int> &sample_numbers() const;
   
  
  inline std::vector< std::shared_ptr<const Measurement> > measurements() const;
  inline std::shared_ptr<const Measurement> measurement( size_t num ) const;
  inline std::shared_ptr<const DetectorAnalysis> detectors_analysis() const;
  */
  
  std::shared_ptr<const MeasurementInfo> m_spec;
};//class SpecFile



#endif //SPEC_UTILS_JS_H