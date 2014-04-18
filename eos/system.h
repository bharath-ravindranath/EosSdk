// Copyright (c) 2014 Arista Networks, Inc.  All rights reserved.
// Arista Networks, Inc. Confidential and Proprietary.

#ifndef EOS_SYSTEM_H
#define EOS_SYSTEM_H

#include <eos/base.h>
#include <eos/base_mgr.h>

namespace eos {

class system_mgr;

/// This class receives changes to system identifying information
class EOS_SDK_PUBLIC system_handler {
 public:
   explicit system_handler(system_mgr *);
   virtual ~system_handler();

   /// Handler called when the hostname changes
   virtual void on_hostname();
   /// Handler called when the fully qualified domain name changes
   virtual void on_fqdn();
   
   /**
    * Handler called once the system identifying information is set.
    *
    * The on_system_info_initialized() method will be called when
    * the serial_number and model_name have been discovered and
    * are accessible via the system_mgr class.
    */
   virtual void on_system_info_initialized();

  protected:
   system_mgr * system_mgr_;
};

/**
 * A manager for identifying information of the system.
 *
 * Create one of these via eos::get_system_mgr() prior to starting the
 * agent main loop. When your eos::agent_handler::on_initialized
 * virtual function is called, the manager is valid for use.
 */
class EOS_SDK_PUBLIC system_mgr : protected base_mgr<system_handler> {
 public:
   virtual ~system_mgr();

   /// Returns the system hostname
   virtual std::string hostname() const = 0;
   /// Returns the system fully qualified domain name
   virtual std::string fqdn() const = 0;

   /// Returns the system serial number
   virtual std::string serial_number() const = 0;
   /// Returns the system model name
   virtual std::string model_name() const = 0;
   /// Returns the hardware revision
   virtual std::string hardware_revision() const = 0;
   /// Returns the running software version
   virtual std::string software_revision() const = 0;
   
 protected:
   system_mgr() EOS_SDK_PRIVATE;
   friend class system_handler;
   
 private:
   EOS_SDK_DISALLOW_COPY_CTOR(system_mgr);
};

} // end namespace eos

#endif // EOS_SYSTEM_H
