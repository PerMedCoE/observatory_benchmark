// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIUsersdIhp024dIobservatory_benchmarkdImultiscale_benchmarkdI2022_09_hackathondIBiodynamodIunit_test_mechanics_friction_singledIcode_scriptsdIbuilddIlibunitmItestmImechanics_dict
#define R__NO_DEPRECATION

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Header files passed as explicit arguments
#include "/Users/hp024/observatory_benchmark/multiscale_benchmark/2022_09_hackathon/Biodynamo/unit_test_mechanics_friction_single/code_scripts/src/custom_ops.h"
#include "/Users/hp024/observatory_benchmark/multiscale_benchmark/2022_09_hackathon/Biodynamo/unit_test_mechanics_friction_single/code_scripts/src/moving_cell.h"
#include "/Users/hp024/observatory_benchmark/multiscale_benchmark/2022_09_hackathon/Biodynamo/unit_test_mechanics_friction_single/code_scripts/src/unit-test-mechanics.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace bdm {
   namespace detail {
   namespace ROOTDict {
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance();
      static TClass *bdmcLcLdetail_Dictionary();

      // Function generating the singleton type initializer
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance()
      {
         static ::ROOT::TGenericClassInfo 
            instance("bdm::detail", 0 /*version*/, "core/util/string.h", 38,
                     ::ROOT::Internal::DefineBehavior((void*)nullptr,(void*)nullptr),
                     &bdmcLcLdetail_Dictionary, 0);
         return &instance;
      }
      // Insure that the inline function is _not_ optimized away by the compiler
      ::ROOT::TGenericClassInfo *(*_R__UNIQUE_DICT_(InitFunctionKeeper))() = &GenerateInitInstance;  
      // Static variable to force the class initialization
      static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstance(); R__UseDummy(_R__UNIQUE_DICT_(Init));

      // Dictionary for non-ClassDef classes
      static TClass *bdmcLcLdetail_Dictionary() {
         return GenerateInitInstance()->GetClass();
      }

   }
}
}

namespace bdm {
   namespace memory_manager_detail {
   namespace ROOTDict {
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance();
      static TClass *bdmcLcLmemory_manager_detail_Dictionary();

      // Function generating the singleton type initializer
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance()
      {
         static ::ROOT::TGenericClassInfo 
            instance("bdm::memory_manager_detail", 0 /*version*/, "core/memory/memory_manager.h", 30,
                     ::ROOT::Internal::DefineBehavior((void*)nullptr,(void*)nullptr),
                     &bdmcLcLmemory_manager_detail_Dictionary, 0);
         return &instance;
      }
      // Insure that the inline function is _not_ optimized away by the compiler
      ::ROOT::TGenericClassInfo *(*_R__UNIQUE_DICT_(InitFunctionKeeper))() = &GenerateInitInstance;  
      // Static variable to force the class initialization
      static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstance(); R__UseDummy(_R__UNIQUE_DICT_(Init));

      // Dictionary for non-ClassDef classes
      static TClass *bdmcLcLmemory_manager_detail_Dictionary() {
         return GenerateInitInstance()->GetClass();
      }

   }
}
}

namespace bdm {
   namespace experimental {
   namespace ROOTDict {
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance();
      static TClass *bdmcLcLexperimental_Dictionary();

      // Function generating the singleton type initializer
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance()
      {
         static ::ROOT::TGenericClassInfo 
            instance("bdm::experimental", 0 /*version*/, "core/simulation.h", 42,
                     ::ROOT::Internal::DefineBehavior((void*)nullptr,(void*)nullptr),
                     &bdmcLcLexperimental_Dictionary, 0);
         return &instance;
      }
      // Insure that the inline function is _not_ optimized away by the compiler
      ::ROOT::TGenericClassInfo *(*_R__UNIQUE_DICT_(InitFunctionKeeper))() = &GenerateInitInstance;  
      // Static variable to force the class initialization
      static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstance(); R__UseDummy(_R__UNIQUE_DICT_(Init));

      // Dictionary for non-ClassDef classes
      static TClass *bdmcLcLexperimental_Dictionary() {
         return GenerateInitInstance()->GetClass();
      }

   }
}
}

namespace bdm {
   namespace in_place_exec_ctxt_detail {
   namespace ROOTDict {
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance();
      static TClass *bdmcLcLin_place_exec_ctxt_detail_Dictionary();

      // Function generating the singleton type initializer
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance()
      {
         static ::ROOT::TGenericClassInfo 
            instance("bdm::in_place_exec_ctxt_detail", 0 /*version*/, "core/execution_context/in_place_exec_ctxt.h", 37,
                     ::ROOT::Internal::DefineBehavior((void*)nullptr,(void*)nullptr),
                     &bdmcLcLin_place_exec_ctxt_detail_Dictionary, 0);
         return &instance;
      }
      // Insure that the inline function is _not_ optimized away by the compiler
      ::ROOT::TGenericClassInfo *(*_R__UNIQUE_DICT_(InitFunctionKeeper))() = &GenerateInitInstance;  
      // Static variable to force the class initialization
      static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstance(); R__UseDummy(_R__UNIQUE_DICT_(Init));

      // Dictionary for non-ClassDef classes
      static TClass *bdmcLcLin_place_exec_ctxt_detail_Dictionary() {
         return GenerateInitInstance()->GetClass();
      }

   }
}
}

namespace bdm {
   namespace neuroscience {
   namespace ROOTDict {
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance();
      static TClass *bdmcLcLneuroscience_Dictionary();

      // Function generating the singleton type initializer
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance()
      {
         static ::ROOT::TGenericClassInfo 
            instance("bdm::neuroscience", 0 /*version*/, "neuroscience/neuron_or_neurite.h", 27,
                     ::ROOT::Internal::DefineBehavior((void*)nullptr,(void*)nullptr),
                     &bdmcLcLneuroscience_Dictionary, 0);
         return &instance;
      }
      // Insure that the inline function is _not_ optimized away by the compiler
      ::ROOT::TGenericClassInfo *(*_R__UNIQUE_DICT_(InitFunctionKeeper))() = &GenerateInitInstance;  
      // Static variable to force the class initialization
      static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstance(); R__UseDummy(_R__UNIQUE_DICT_(Init));

      // Dictionary for non-ClassDef classes
      static TClass *bdmcLcLneuroscience_Dictionary() {
         return GenerateInitInstance()->GetClass();
      }

   }
}
}

namespace ROOT {
   static TClass *bdmcLcLAgentPointerlEbdmcLcLAgentgR_Dictionary();
   static void bdmcLcLAgentPointerlEbdmcLcLAgentgR_TClassManip(TClass*);
   static void *new_bdmcLcLAgentPointerlEbdmcLcLAgentgR(void *p = nullptr);
   static void *newArray_bdmcLcLAgentPointerlEbdmcLcLAgentgR(Long_t size, void *p);
   static void delete_bdmcLcLAgentPointerlEbdmcLcLAgentgR(void *p);
   static void deleteArray_bdmcLcLAgentPointerlEbdmcLcLAgentgR(void *p);
   static void destruct_bdmcLcLAgentPointerlEbdmcLcLAgentgR(void *p);
   static void streamer_bdmcLcLAgentPointerlEbdmcLcLAgentgR(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::bdm::AgentPointer<bdm::Agent>*)
   {
      ::bdm::AgentPointer<bdm::Agent> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::bdm::AgentPointer<bdm::Agent> >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("bdm::AgentPointer<bdm::Agent>", ::bdm::AgentPointer<bdm::Agent>::Class_Version(), "core/agent/agent_pointer.h", 58,
                  typeid(::bdm::AgentPointer<bdm::Agent>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &bdmcLcLAgentPointerlEbdmcLcLAgentgR_Dictionary, isa_proxy, 21,
                  sizeof(::bdm::AgentPointer<bdm::Agent>) );
      instance.SetNew(&new_bdmcLcLAgentPointerlEbdmcLcLAgentgR);
      instance.SetNewArray(&newArray_bdmcLcLAgentPointerlEbdmcLcLAgentgR);
      instance.SetDelete(&delete_bdmcLcLAgentPointerlEbdmcLcLAgentgR);
      instance.SetDeleteArray(&deleteArray_bdmcLcLAgentPointerlEbdmcLcLAgentgR);
      instance.SetDestructor(&destruct_bdmcLcLAgentPointerlEbdmcLcLAgentgR);
      instance.SetStreamerFunc(&streamer_bdmcLcLAgentPointerlEbdmcLcLAgentgR);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::bdm::AgentPointer<bdm::Agent>*)
   {
      return GenerateInitInstanceLocal((::bdm::AgentPointer<bdm::Agent>*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::bdm::AgentPointer<bdm::Agent>*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *bdmcLcLAgentPointerlEbdmcLcLAgentgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::bdm::AgentPointer<bdm::Agent>*)nullptr)->GetClass();
      bdmcLcLAgentPointerlEbdmcLcLAgentgR_TClassManip(theClass);
   return theClass;
   }

   static void bdmcLcLAgentPointerlEbdmcLcLAgentgR_TClassManip(TClass* theClass){
      theClass->CreateAttributeMap();
      TDictAttributeMap* attrMap( theClass->GetAttributeMap() );
      attrMap->AddProperty("noStreamer","true");
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *bdmcLcLSharedDatalEULong64_tgRcLcLIterator_Dictionary();
   static void bdmcLcLSharedDatalEULong64_tgRcLcLIterator_TClassManip(TClass*);
   static void *new_bdmcLcLSharedDatalEULong64_tgRcLcLIterator(void *p = nullptr);
   static void *newArray_bdmcLcLSharedDatalEULong64_tgRcLcLIterator(Long_t size, void *p);
   static void delete_bdmcLcLSharedDatalEULong64_tgRcLcLIterator(void *p);
   static void deleteArray_bdmcLcLSharedDatalEULong64_tgRcLcLIterator(void *p);
   static void destruct_bdmcLcLSharedDatalEULong64_tgRcLcLIterator(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::bdm::SharedData<ULong64_t>::Iterator*)
   {
      ::bdm::SharedData<ULong64_t>::Iterator *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::bdm::SharedData<ULong64_t>::Iterator));
      static ::ROOT::TGenericClassInfo 
         instance("bdm::SharedData<ULong64_t>::Iterator", "core/container/shared_data.h", 64,
                  typeid(::bdm::SharedData<ULong64_t>::Iterator), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &bdmcLcLSharedDatalEULong64_tgRcLcLIterator_Dictionary, isa_proxy, 4,
                  sizeof(::bdm::SharedData<ULong64_t>::Iterator) );
      instance.SetNew(&new_bdmcLcLSharedDatalEULong64_tgRcLcLIterator);
      instance.SetNewArray(&newArray_bdmcLcLSharedDatalEULong64_tgRcLcLIterator);
      instance.SetDelete(&delete_bdmcLcLSharedDatalEULong64_tgRcLcLIterator);
      instance.SetDeleteArray(&deleteArray_bdmcLcLSharedDatalEULong64_tgRcLcLIterator);
      instance.SetDestructor(&destruct_bdmcLcLSharedDatalEULong64_tgRcLcLIterator);

      ::ROOT::AddClassAlternate("bdm::SharedData<ULong64_t>::Iterator","bdm::SharedData<unsigned long long>::Iterator");
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::bdm::SharedData<ULong64_t>::Iterator*)
   {
      return GenerateInitInstanceLocal((::bdm::SharedData<ULong64_t>::Iterator*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::bdm::SharedData<ULong64_t>::Iterator*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *bdmcLcLSharedDatalEULong64_tgRcLcLIterator_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::bdm::SharedData<ULong64_t>::Iterator*)nullptr)->GetClass();
      bdmcLcLSharedDatalEULong64_tgRcLcLIterator_TClassManip(theClass);
   return theClass;
   }

   static void bdmcLcLSharedDatalEULong64_tgRcLcLIterator_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *bdmcLcLSharedDatalEdoublegR_Dictionary();
   static void bdmcLcLSharedDatalEdoublegR_TClassManip(TClass*);
   static void *new_bdmcLcLSharedDatalEdoublegR(void *p = nullptr);
   static void *newArray_bdmcLcLSharedDatalEdoublegR(Long_t size, void *p);
   static void delete_bdmcLcLSharedDatalEdoublegR(void *p);
   static void deleteArray_bdmcLcLSharedDatalEdoublegR(void *p);
   static void destruct_bdmcLcLSharedDatalEdoublegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::bdm::SharedData<double>*)
   {
      ::bdm::SharedData<double> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::bdm::SharedData<double> >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("bdm::SharedData<double>", ::bdm::SharedData<double>::Class_Version(), "core/container/shared_data.h", 34,
                  typeid(::bdm::SharedData<double>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &bdmcLcLSharedDatalEdoublegR_Dictionary, isa_proxy, 4,
                  sizeof(::bdm::SharedData<double>) );
      instance.SetNew(&new_bdmcLcLSharedDatalEdoublegR);
      instance.SetNewArray(&newArray_bdmcLcLSharedDatalEdoublegR);
      instance.SetDelete(&delete_bdmcLcLSharedDatalEdoublegR);
      instance.SetDeleteArray(&deleteArray_bdmcLcLSharedDatalEdoublegR);
      instance.SetDestructor(&destruct_bdmcLcLSharedDatalEdoublegR);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::bdm::SharedData<double>*)
   {
      return GenerateInitInstanceLocal((::bdm::SharedData<double>*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::bdm::SharedData<double>*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *bdmcLcLSharedDatalEdoublegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::bdm::SharedData<double>*)nullptr)->GetClass();
      bdmcLcLSharedDatalEdoublegR_TClassManip(theClass);
   return theClass;
   }

   static void bdmcLcLSharedDatalEdoublegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *bdmcLcLSharedDatalEfloatgR_Dictionary();
   static void bdmcLcLSharedDatalEfloatgR_TClassManip(TClass*);
   static void *new_bdmcLcLSharedDatalEfloatgR(void *p = nullptr);
   static void *newArray_bdmcLcLSharedDatalEfloatgR(Long_t size, void *p);
   static void delete_bdmcLcLSharedDatalEfloatgR(void *p);
   static void deleteArray_bdmcLcLSharedDatalEfloatgR(void *p);
   static void destruct_bdmcLcLSharedDatalEfloatgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::bdm::SharedData<float>*)
   {
      ::bdm::SharedData<float> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::bdm::SharedData<float> >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("bdm::SharedData<float>", ::bdm::SharedData<float>::Class_Version(), "core/container/shared_data.h", 34,
                  typeid(::bdm::SharedData<float>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &bdmcLcLSharedDatalEfloatgR_Dictionary, isa_proxy, 4,
                  sizeof(::bdm::SharedData<float>) );
      instance.SetNew(&new_bdmcLcLSharedDatalEfloatgR);
      instance.SetNewArray(&newArray_bdmcLcLSharedDatalEfloatgR);
      instance.SetDelete(&delete_bdmcLcLSharedDatalEfloatgR);
      instance.SetDeleteArray(&deleteArray_bdmcLcLSharedDatalEfloatgR);
      instance.SetDestructor(&destruct_bdmcLcLSharedDatalEfloatgR);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::bdm::SharedData<float>*)
   {
      return GenerateInitInstanceLocal((::bdm::SharedData<float>*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::bdm::SharedData<float>*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *bdmcLcLSharedDatalEfloatgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::bdm::SharedData<float>*)nullptr)->GetClass();
      bdmcLcLSharedDatalEfloatgR_TClassManip(theClass);
   return theClass;
   }

   static void bdmcLcLSharedDatalEfloatgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *bdmcLcLProgressBar_Dictionary();
   static void bdmcLcLProgressBar_TClassManip(TClass*);
   static void *new_bdmcLcLProgressBar(void *p = nullptr);
   static void *newArray_bdmcLcLProgressBar(Long_t size, void *p);
   static void delete_bdmcLcLProgressBar(void *p);
   static void deleteArray_bdmcLcLProgressBar(void *p);
   static void destruct_bdmcLcLProgressBar(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::bdm::ProgressBar*)
   {
      ::bdm::ProgressBar *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::bdm::ProgressBar));
      static ::ROOT::TGenericClassInfo 
         instance("bdm::ProgressBar", "core/util/progress_bar.h", 40,
                  typeid(::bdm::ProgressBar), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &bdmcLcLProgressBar_Dictionary, isa_proxy, 4,
                  sizeof(::bdm::ProgressBar) );
      instance.SetNew(&new_bdmcLcLProgressBar);
      instance.SetNewArray(&newArray_bdmcLcLProgressBar);
      instance.SetDelete(&delete_bdmcLcLProgressBar);
      instance.SetDeleteArray(&deleteArray_bdmcLcLProgressBar);
      instance.SetDestructor(&destruct_bdmcLcLProgressBar);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::bdm::ProgressBar*)
   {
      return GenerateInitInstanceLocal((::bdm::ProgressBar*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::bdm::ProgressBar*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *bdmcLcLProgressBar_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::bdm::ProgressBar*)nullptr)->GetClass();
      bdmcLcLProgressBar_TClassManip(theClass);
   return theClass;
   }

   static void bdmcLcLProgressBar_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static void delete_bdmcLcLVectorField(void *p);
   static void deleteArray_bdmcLcLVectorField(void *p);
   static void destruct_bdmcLcLVectorField(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::bdm::VectorField*)
   {
      ::bdm::VectorField *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::bdm::VectorField >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("bdm::VectorField", ::bdm::VectorField::Class_Version(), "core/diffusion/continuum_interface.h", 148,
                  typeid(::bdm::VectorField), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::bdm::VectorField::Dictionary, isa_proxy, 4,
                  sizeof(::bdm::VectorField) );
      instance.SetDelete(&delete_bdmcLcLVectorField);
      instance.SetDeleteArray(&deleteArray_bdmcLcLVectorField);
      instance.SetDestructor(&destruct_bdmcLcLVectorField);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::bdm::VectorField*)
   {
      return GenerateInitInstanceLocal((::bdm::VectorField*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::bdm::VectorField*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_bdmcLcLMoving_cell(void *p = nullptr);
   static void delete_bdmcLcLMoving_cell(void *p);
   static void deleteArray_bdmcLcLMoving_cell(void *p);
   static void destruct_bdmcLcLMoving_cell(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::bdm::Moving_cell*)
   {
      ::bdm::Moving_cell *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::bdm::Moving_cell >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("bdm::Moving_cell", ::bdm::Moving_cell::Class_Version(), "moving_cell.h", 9,
                  typeid(::bdm::Moving_cell), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::bdm::Moving_cell::Dictionary, isa_proxy, 4,
                  sizeof(::bdm::Moving_cell) );
      instance.SetNew(&new_bdmcLcLMoving_cell);
      instance.SetDelete(&delete_bdmcLcLMoving_cell);
      instance.SetDeleteArray(&deleteArray_bdmcLcLMoving_cell);
      instance.SetDestructor(&destruct_bdmcLcLMoving_cell);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::bdm::Moving_cell*)
   {
      return GenerateInitInstanceLocal((::bdm::Moving_cell*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::bdm::Moving_cell*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static TClass *bdmcLcLDissipativeForce_Dictionary();
   static void bdmcLcLDissipativeForce_TClassManip(TClass*);
   static void *new_bdmcLcLDissipativeForce(void *p = nullptr);
   static void *newArray_bdmcLcLDissipativeForce(Long_t size, void *p);
   static void delete_bdmcLcLDissipativeForce(void *p);
   static void deleteArray_bdmcLcLDissipativeForce(void *p);
   static void destruct_bdmcLcLDissipativeForce(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::bdm::DissipativeForce*)
   {
      ::bdm::DissipativeForce *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::bdm::DissipativeForce));
      static ::ROOT::TGenericClassInfo 
         instance("bdm::DissipativeForce", "", 23,
                  typeid(::bdm::DissipativeForce), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &bdmcLcLDissipativeForce_Dictionary, isa_proxy, 4,
                  sizeof(::bdm::DissipativeForce) );
      instance.SetNew(&new_bdmcLcLDissipativeForce);
      instance.SetNewArray(&newArray_bdmcLcLDissipativeForce);
      instance.SetDelete(&delete_bdmcLcLDissipativeForce);
      instance.SetDeleteArray(&deleteArray_bdmcLcLDissipativeForce);
      instance.SetDestructor(&destruct_bdmcLcLDissipativeForce);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::bdm::DissipativeForce*)
   {
      return GenerateInitInstanceLocal((::bdm::DissipativeForce*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::bdm::DissipativeForce*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *bdmcLcLDissipativeForce_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::bdm::DissipativeForce*)nullptr)->GetClass();
      bdmcLcLDissipativeForce_TClassManip(theClass);
   return theClass;
   }

   static void bdmcLcLDissipativeForce_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *bdmcLcLApplyForce_Dictionary();
   static void bdmcLcLApplyForce_TClassManip(TClass*);
   static void *new_bdmcLcLApplyForce(void *p = nullptr);
   static void *newArray_bdmcLcLApplyForce(Long_t size, void *p);
   static void delete_bdmcLcLApplyForce(void *p);
   static void deleteArray_bdmcLcLApplyForce(void *p);
   static void destruct_bdmcLcLApplyForce(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::bdm::ApplyForce*)
   {
      ::bdm::ApplyForce *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::bdm::ApplyForce));
      static ::ROOT::TGenericClassInfo 
         instance("bdm::ApplyForce", "", 37,
                  typeid(::bdm::ApplyForce), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &bdmcLcLApplyForce_Dictionary, isa_proxy, 4,
                  sizeof(::bdm::ApplyForce) );
      instance.SetNew(&new_bdmcLcLApplyForce);
      instance.SetNewArray(&newArray_bdmcLcLApplyForce);
      instance.SetDelete(&delete_bdmcLcLApplyForce);
      instance.SetDeleteArray(&deleteArray_bdmcLcLApplyForce);
      instance.SetDestructor(&destruct_bdmcLcLApplyForce);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::bdm::ApplyForce*)
   {
      return GenerateInitInstanceLocal((::bdm::ApplyForce*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::bdm::ApplyForce*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *bdmcLcLApplyForce_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::bdm::ApplyForce*)nullptr)->GetClass();
      bdmcLcLApplyForce_TClassManip(theClass);
   return theClass;
   }

   static void bdmcLcLApplyForce_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *bdmcLcLTrackPosition_Dictionary();
   static void bdmcLcLTrackPosition_TClassManip(TClass*);
   static void *new_bdmcLcLTrackPosition(void *p = nullptr);
   static void *newArray_bdmcLcLTrackPosition(Long_t size, void *p);
   static void delete_bdmcLcLTrackPosition(void *p);
   static void deleteArray_bdmcLcLTrackPosition(void *p);
   static void destruct_bdmcLcLTrackPosition(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::bdm::TrackPosition*)
   {
      ::bdm::TrackPosition *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::bdm::TrackPosition));
      static ::ROOT::TGenericClassInfo 
         instance("bdm::TrackPosition", "", 54,
                  typeid(::bdm::TrackPosition), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &bdmcLcLTrackPosition_Dictionary, isa_proxy, 4,
                  sizeof(::bdm::TrackPosition) );
      instance.SetNew(&new_bdmcLcLTrackPosition);
      instance.SetNewArray(&newArray_bdmcLcLTrackPosition);
      instance.SetDelete(&delete_bdmcLcLTrackPosition);
      instance.SetDeleteArray(&deleteArray_bdmcLcLTrackPosition);
      instance.SetDestructor(&destruct_bdmcLcLTrackPosition);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::bdm::TrackPosition*)
   {
      return GenerateInitInstanceLocal((::bdm::TrackPosition*)nullptr);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::bdm::TrackPosition*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *bdmcLcLTrackPosition_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::bdm::TrackPosition*)nullptr)->GetClass();
      bdmcLcLTrackPosition_TClassManip(theClass);
   return theClass;
   }

   static void bdmcLcLTrackPosition_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace bdm {
//______________________________________________________________________________
template <> atomic_TClass_ptr AgentPointer<bdm::Agent>::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
template <> const char *AgentPointer<bdm::Agent>::Class_Name()
{
   return "bdm::AgentPointer<bdm::Agent>";
}

//______________________________________________________________________________
template <> const char *AgentPointer<bdm::Agent>::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::bdm::AgentPointer<bdm::Agent>*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
template <> int AgentPointer<bdm::Agent>::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::bdm::AgentPointer<bdm::Agent>*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
template <> TClass *AgentPointer<bdm::Agent>::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::bdm::AgentPointer<bdm::Agent>*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
template <> TClass *AgentPointer<bdm::Agent>::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::bdm::AgentPointer<bdm::Agent>*)nullptr)->GetClass(); }
   return fgIsA;
}

} // namespace bdm
namespace bdm {
//______________________________________________________________________________
template <> atomic_TClass_ptr SharedData<double>::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
template <> const char *SharedData<double>::Class_Name()
{
   return "bdm::SharedData<double>";
}

//______________________________________________________________________________
template <> const char *SharedData<double>::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::bdm::SharedData<double>*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
template <> int SharedData<double>::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::bdm::SharedData<double>*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
template <> TClass *SharedData<double>::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::bdm::SharedData<double>*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
template <> TClass *SharedData<double>::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::bdm::SharedData<double>*)nullptr)->GetClass(); }
   return fgIsA;
}

} // namespace bdm
namespace bdm {
//______________________________________________________________________________
template <> atomic_TClass_ptr SharedData<float>::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
template <> const char *SharedData<float>::Class_Name()
{
   return "bdm::SharedData<float>";
}

//______________________________________________________________________________
template <> const char *SharedData<float>::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::bdm::SharedData<float>*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
template <> int SharedData<float>::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::bdm::SharedData<float>*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
template <> TClass *SharedData<float>::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::bdm::SharedData<float>*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
template <> TClass *SharedData<float>::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::bdm::SharedData<float>*)nullptr)->GetClass(); }
   return fgIsA;
}

} // namespace bdm
namespace bdm {
//______________________________________________________________________________
atomic_TClass_ptr VectorField::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *VectorField::Class_Name()
{
   return "bdm::VectorField";
}

//______________________________________________________________________________
const char *VectorField::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::bdm::VectorField*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int VectorField::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::bdm::VectorField*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *VectorField::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::bdm::VectorField*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *VectorField::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::bdm::VectorField*)nullptr)->GetClass(); }
   return fgIsA;
}

} // namespace bdm
namespace bdm {
//______________________________________________________________________________
atomic_TClass_ptr Moving_cell::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *Moving_cell::Class_Name()
{
   return "bdm::Moving_cell";
}

//______________________________________________________________________________
const char *Moving_cell::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::bdm::Moving_cell*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int Moving_cell::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::bdm::Moving_cell*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Moving_cell::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::bdm::Moving_cell*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Moving_cell::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::bdm::Moving_cell*)nullptr)->GetClass(); }
   return fgIsA;
}

} // namespace bdm
namespace ROOT {
   // Wrappers around operator new
   static void *new_bdmcLcLAgentPointerlEbdmcLcLAgentgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::bdm::AgentPointer<bdm::Agent> : new ::bdm::AgentPointer<bdm::Agent>;
   }
   static void *newArray_bdmcLcLAgentPointerlEbdmcLcLAgentgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::bdm::AgentPointer<bdm::Agent>[nElements] : new ::bdm::AgentPointer<bdm::Agent>[nElements];
   }
   // Wrapper around operator delete
   static void delete_bdmcLcLAgentPointerlEbdmcLcLAgentgR(void *p) {
      delete ((::bdm::AgentPointer<bdm::Agent>*)p);
   }
   static void deleteArray_bdmcLcLAgentPointerlEbdmcLcLAgentgR(void *p) {
      delete [] ((::bdm::AgentPointer<bdm::Agent>*)p);
   }
   static void destruct_bdmcLcLAgentPointerlEbdmcLcLAgentgR(void *p) {
      typedef ::bdm::AgentPointer<bdm::Agent> current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_bdmcLcLAgentPointerlEbdmcLcLAgentgR(TBuffer &buf, void *obj) {
      ((::bdm::AgentPointer<bdm::Agent>*)obj)->::bdm::AgentPointer<bdm::Agent>::Streamer(buf);
   }
} // end of namespace ROOT for class ::bdm::AgentPointer<bdm::Agent>

namespace ROOT {
   // Wrappers around operator new
   static void *new_bdmcLcLSharedDatalEULong64_tgRcLcLIterator(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::bdm::SharedData<ULong64_t>::Iterator : new ::bdm::SharedData<ULong64_t>::Iterator;
   }
   static void *newArray_bdmcLcLSharedDatalEULong64_tgRcLcLIterator(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::bdm::SharedData<ULong64_t>::Iterator[nElements] : new ::bdm::SharedData<ULong64_t>::Iterator[nElements];
   }
   // Wrapper around operator delete
   static void delete_bdmcLcLSharedDatalEULong64_tgRcLcLIterator(void *p) {
      delete ((::bdm::SharedData<ULong64_t>::Iterator*)p);
   }
   static void deleteArray_bdmcLcLSharedDatalEULong64_tgRcLcLIterator(void *p) {
      delete [] ((::bdm::SharedData<ULong64_t>::Iterator*)p);
   }
   static void destruct_bdmcLcLSharedDatalEULong64_tgRcLcLIterator(void *p) {
      typedef ::bdm::SharedData<ULong64_t>::Iterator current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::bdm::SharedData<ULong64_t>::Iterator

namespace bdm {
//______________________________________________________________________________
template <> void SharedData<double>::Streamer(TBuffer &R__b)
{
   // Stream an object of class bdm::SharedData<double>.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(bdm::SharedData<double>::Class(),this);
   } else {
      R__b.WriteClassBuffer(bdm::SharedData<double>::Class(),this);
   }
}

} // namespace bdm
namespace ROOT {
   // Wrappers around operator new
   static void *new_bdmcLcLSharedDatalEdoublegR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::bdm::SharedData<double> : new ::bdm::SharedData<double>;
   }
   static void *newArray_bdmcLcLSharedDatalEdoublegR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::bdm::SharedData<double>[nElements] : new ::bdm::SharedData<double>[nElements];
   }
   // Wrapper around operator delete
   static void delete_bdmcLcLSharedDatalEdoublegR(void *p) {
      delete ((::bdm::SharedData<double>*)p);
   }
   static void deleteArray_bdmcLcLSharedDatalEdoublegR(void *p) {
      delete [] ((::bdm::SharedData<double>*)p);
   }
   static void destruct_bdmcLcLSharedDatalEdoublegR(void *p) {
      typedef ::bdm::SharedData<double> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::bdm::SharedData<double>

namespace bdm {
//______________________________________________________________________________
template <> void SharedData<float>::Streamer(TBuffer &R__b)
{
   // Stream an object of class bdm::SharedData<float>.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(bdm::SharedData<float>::Class(),this);
   } else {
      R__b.WriteClassBuffer(bdm::SharedData<float>::Class(),this);
   }
}

} // namespace bdm
namespace ROOT {
   // Wrappers around operator new
   static void *new_bdmcLcLSharedDatalEfloatgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::bdm::SharedData<float> : new ::bdm::SharedData<float>;
   }
   static void *newArray_bdmcLcLSharedDatalEfloatgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::bdm::SharedData<float>[nElements] : new ::bdm::SharedData<float>[nElements];
   }
   // Wrapper around operator delete
   static void delete_bdmcLcLSharedDatalEfloatgR(void *p) {
      delete ((::bdm::SharedData<float>*)p);
   }
   static void deleteArray_bdmcLcLSharedDatalEfloatgR(void *p) {
      delete [] ((::bdm::SharedData<float>*)p);
   }
   static void destruct_bdmcLcLSharedDatalEfloatgR(void *p) {
      typedef ::bdm::SharedData<float> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::bdm::SharedData<float>

namespace ROOT {
   // Wrappers around operator new
   static void *new_bdmcLcLProgressBar(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::bdm::ProgressBar : new ::bdm::ProgressBar;
   }
   static void *newArray_bdmcLcLProgressBar(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::bdm::ProgressBar[nElements] : new ::bdm::ProgressBar[nElements];
   }
   // Wrapper around operator delete
   static void delete_bdmcLcLProgressBar(void *p) {
      delete ((::bdm::ProgressBar*)p);
   }
   static void deleteArray_bdmcLcLProgressBar(void *p) {
      delete [] ((::bdm::ProgressBar*)p);
   }
   static void destruct_bdmcLcLProgressBar(void *p) {
      typedef ::bdm::ProgressBar current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::bdm::ProgressBar

namespace bdm {
//______________________________________________________________________________
void VectorField::Streamer(TBuffer &R__b)
{
   // Stream an object of class bdm::VectorField.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(bdm::VectorField::Class(),this);
   } else {
      R__b.WriteClassBuffer(bdm::VectorField::Class(),this);
   }
}

} // namespace bdm
namespace ROOT {
   // Wrapper around operator delete
   static void delete_bdmcLcLVectorField(void *p) {
      delete ((::bdm::VectorField*)p);
   }
   static void deleteArray_bdmcLcLVectorField(void *p) {
      delete [] ((::bdm::VectorField*)p);
   }
   static void destruct_bdmcLcLVectorField(void *p) {
      typedef ::bdm::VectorField current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::bdm::VectorField

namespace bdm {
//______________________________________________________________________________
void Moving_cell::Streamer(TBuffer &R__b)
{
   // Stream an object of class bdm::Moving_cell.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(bdm::Moving_cell::Class(),this);
   } else {
      R__b.WriteClassBuffer(bdm::Moving_cell::Class(),this);
   }
}

} // namespace bdm
namespace ROOT {
   // Wrappers around operator new
   static void *new_bdmcLcLMoving_cell(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::bdm::Moving_cell( (TRootIOCtor *)nullptr ) : new ::bdm::Moving_cell( (TRootIOCtor *)nullptr );
   }
   // Wrapper around operator delete
   static void delete_bdmcLcLMoving_cell(void *p) {
      delete ((::bdm::Moving_cell*)p);
   }
   static void deleteArray_bdmcLcLMoving_cell(void *p) {
      delete [] ((::bdm::Moving_cell*)p);
   }
   static void destruct_bdmcLcLMoving_cell(void *p) {
      typedef ::bdm::Moving_cell current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::bdm::Moving_cell

namespace ROOT {
   // Wrappers around operator new
   static void *new_bdmcLcLDissipativeForce(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::bdm::DissipativeForce : new ::bdm::DissipativeForce;
   }
   static void *newArray_bdmcLcLDissipativeForce(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::bdm::DissipativeForce[nElements] : new ::bdm::DissipativeForce[nElements];
   }
   // Wrapper around operator delete
   static void delete_bdmcLcLDissipativeForce(void *p) {
      delete ((::bdm::DissipativeForce*)p);
   }
   static void deleteArray_bdmcLcLDissipativeForce(void *p) {
      delete [] ((::bdm::DissipativeForce*)p);
   }
   static void destruct_bdmcLcLDissipativeForce(void *p) {
      typedef ::bdm::DissipativeForce current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::bdm::DissipativeForce

namespace ROOT {
   // Wrappers around operator new
   static void *new_bdmcLcLApplyForce(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::bdm::ApplyForce : new ::bdm::ApplyForce;
   }
   static void *newArray_bdmcLcLApplyForce(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::bdm::ApplyForce[nElements] : new ::bdm::ApplyForce[nElements];
   }
   // Wrapper around operator delete
   static void delete_bdmcLcLApplyForce(void *p) {
      delete ((::bdm::ApplyForce*)p);
   }
   static void deleteArray_bdmcLcLApplyForce(void *p) {
      delete [] ((::bdm::ApplyForce*)p);
   }
   static void destruct_bdmcLcLApplyForce(void *p) {
      typedef ::bdm::ApplyForce current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::bdm::ApplyForce

namespace ROOT {
   // Wrappers around operator new
   static void *new_bdmcLcLTrackPosition(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::bdm::TrackPosition : new ::bdm::TrackPosition;
   }
   static void *newArray_bdmcLcLTrackPosition(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::bdm::TrackPosition[nElements] : new ::bdm::TrackPosition[nElements];
   }
   // Wrapper around operator delete
   static void delete_bdmcLcLTrackPosition(void *p) {
      delete ((::bdm::TrackPosition*)p);
   }
   static void deleteArray_bdmcLcLTrackPosition(void *p) {
      delete [] ((::bdm::TrackPosition*)p);
   }
   static void destruct_bdmcLcLTrackPosition(void *p) {
      typedef ::bdm::TrackPosition current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::bdm::TrackPosition

namespace ROOT {
   static TClass *vectorlEbdmcLcLSpinlockmUgR_Dictionary();
   static void vectorlEbdmcLcLSpinlockmUgR_TClassManip(TClass*);
   static void *new_vectorlEbdmcLcLSpinlockmUgR(void *p = nullptr);
   static void *newArray_vectorlEbdmcLcLSpinlockmUgR(Long_t size, void *p);
   static void delete_vectorlEbdmcLcLSpinlockmUgR(void *p);
   static void deleteArray_vectorlEbdmcLcLSpinlockmUgR(void *p);
   static void destruct_vectorlEbdmcLcLSpinlockmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<bdm::Spinlock*>*)
   {
      vector<bdm::Spinlock*> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<bdm::Spinlock*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<bdm::Spinlock*>", -2, "c++/v1/vector", 478,
                  typeid(vector<bdm::Spinlock*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEbdmcLcLSpinlockmUgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<bdm::Spinlock*>) );
      instance.SetNew(&new_vectorlEbdmcLcLSpinlockmUgR);
      instance.SetNewArray(&newArray_vectorlEbdmcLcLSpinlockmUgR);
      instance.SetDelete(&delete_vectorlEbdmcLcLSpinlockmUgR);
      instance.SetDeleteArray(&deleteArray_vectorlEbdmcLcLSpinlockmUgR);
      instance.SetDestructor(&destruct_vectorlEbdmcLcLSpinlockmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<bdm::Spinlock*> >()));

      ::ROOT::AddClassAlternate("vector<bdm::Spinlock*>","std::__1::vector<bdm::Spinlock*, std::__1::allocator<bdm::Spinlock*>>");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<bdm::Spinlock*>*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEbdmcLcLSpinlockmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<bdm::Spinlock*>*)nullptr)->GetClass();
      vectorlEbdmcLcLSpinlockmUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEbdmcLcLSpinlockmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEbdmcLcLSpinlockmUgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<bdm::Spinlock*> : new vector<bdm::Spinlock*>;
   }
   static void *newArray_vectorlEbdmcLcLSpinlockmUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<bdm::Spinlock*>[nElements] : new vector<bdm::Spinlock*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEbdmcLcLSpinlockmUgR(void *p) {
      delete ((vector<bdm::Spinlock*>*)p);
   }
   static void deleteArray_vectorlEbdmcLcLSpinlockmUgR(void *p) {
      delete [] ((vector<bdm::Spinlock*>*)p);
   }
   static void destruct_vectorlEbdmcLcLSpinlockmUgR(void *p) {
      typedef vector<bdm::Spinlock*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<bdm::Spinlock*>

namespace ROOT {
   static TClass *vectorlEbdmcLcLSharedDatalEvectorlEbdmcLcLAgentUidgRsPgRcLcLAlignedTgR_Dictionary();
   static void vectorlEbdmcLcLSharedDatalEvectorlEbdmcLcLAgentUidgRsPgRcLcLAlignedTgR_TClassManip(TClass*);
   static void *new_vectorlEbdmcLcLSharedDatalEvectorlEbdmcLcLAgentUidgRsPgRcLcLAlignedTgR(void *p = nullptr);
   static void *newArray_vectorlEbdmcLcLSharedDatalEvectorlEbdmcLcLAgentUidgRsPgRcLcLAlignedTgR(Long_t size, void *p);
   static void delete_vectorlEbdmcLcLSharedDatalEvectorlEbdmcLcLAgentUidgRsPgRcLcLAlignedTgR(void *p);
   static void deleteArray_vectorlEbdmcLcLSharedDatalEvectorlEbdmcLcLAgentUidgRsPgRcLcLAlignedTgR(void *p);
   static void destruct_vectorlEbdmcLcLSharedDatalEvectorlEbdmcLcLAgentUidgRsPgRcLcLAlignedTgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<bdm::SharedData<vector<bdm::AgentUid> >::AlignedT>*)
   {
      vector<bdm::SharedData<vector<bdm::AgentUid> >::AlignedT> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<bdm::SharedData<vector<bdm::AgentUid> >::AlignedT>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<bdm::SharedData<vector<bdm::AgentUid> >::AlignedT>", -2, "c++/v1/vector", 478,
                  typeid(vector<bdm::SharedData<vector<bdm::AgentUid> >::AlignedT>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEbdmcLcLSharedDatalEvectorlEbdmcLcLAgentUidgRsPgRcLcLAlignedTgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<bdm::SharedData<vector<bdm::AgentUid> >::AlignedT>) );
      instance.SetNew(&new_vectorlEbdmcLcLSharedDatalEvectorlEbdmcLcLAgentUidgRsPgRcLcLAlignedTgR);
      instance.SetNewArray(&newArray_vectorlEbdmcLcLSharedDatalEvectorlEbdmcLcLAgentUidgRsPgRcLcLAlignedTgR);
      instance.SetDelete(&delete_vectorlEbdmcLcLSharedDatalEvectorlEbdmcLcLAgentUidgRsPgRcLcLAlignedTgR);
      instance.SetDeleteArray(&deleteArray_vectorlEbdmcLcLSharedDatalEvectorlEbdmcLcLAgentUidgRsPgRcLcLAlignedTgR);
      instance.SetDestructor(&destruct_vectorlEbdmcLcLSharedDatalEvectorlEbdmcLcLAgentUidgRsPgRcLcLAlignedTgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<bdm::SharedData<vector<bdm::AgentUid> >::AlignedT> >()));

      ::ROOT::AddClassAlternate("vector<bdm::SharedData<vector<bdm::AgentUid> >::AlignedT>","std::__1::vector<bdm::SharedData<std::__1::vector<bdm::AgentUid, std::__1::allocator<bdm::AgentUid>>>::AlignedT, std::__1::allocator<bdm::SharedData<std::__1::vector<bdm::AgentUid, std::__1::allocator<bdm::AgentUid>>>::AlignedT>>");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<bdm::SharedData<vector<bdm::AgentUid> >::AlignedT>*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEbdmcLcLSharedDatalEvectorlEbdmcLcLAgentUidgRsPgRcLcLAlignedTgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<bdm::SharedData<vector<bdm::AgentUid> >::AlignedT>*)nullptr)->GetClass();
      vectorlEbdmcLcLSharedDatalEvectorlEbdmcLcLAgentUidgRsPgRcLcLAlignedTgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEbdmcLcLSharedDatalEvectorlEbdmcLcLAgentUidgRsPgRcLcLAlignedTgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEbdmcLcLSharedDatalEvectorlEbdmcLcLAgentUidgRsPgRcLcLAlignedTgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<bdm::SharedData<vector<bdm::AgentUid> >::AlignedT> : new vector<bdm::SharedData<vector<bdm::AgentUid> >::AlignedT>;
   }
   static void *newArray_vectorlEbdmcLcLSharedDatalEvectorlEbdmcLcLAgentUidgRsPgRcLcLAlignedTgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<bdm::SharedData<vector<bdm::AgentUid> >::AlignedT>[nElements] : new vector<bdm::SharedData<vector<bdm::AgentUid> >::AlignedT>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEbdmcLcLSharedDatalEvectorlEbdmcLcLAgentUidgRsPgRcLcLAlignedTgR(void *p) {
      delete ((vector<bdm::SharedData<vector<bdm::AgentUid> >::AlignedT>*)p);
   }
   static void deleteArray_vectorlEbdmcLcLSharedDatalEvectorlEbdmcLcLAgentUidgRsPgRcLcLAlignedTgR(void *p) {
      delete [] ((vector<bdm::SharedData<vector<bdm::AgentUid> >::AlignedT>*)p);
   }
   static void destruct_vectorlEbdmcLcLSharedDatalEvectorlEbdmcLcLAgentUidgRsPgRcLcLAlignedTgR(void *p) {
      typedef vector<bdm::SharedData<vector<bdm::AgentUid> >::AlignedT> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<bdm::SharedData<vector<bdm::AgentUid> >::AlignedT>

namespace ROOT {
   static TClass *vectorlEbdmcLcLSharedDatalEfloatgRcLcLAlignedTgR_Dictionary();
   static void vectorlEbdmcLcLSharedDatalEfloatgRcLcLAlignedTgR_TClassManip(TClass*);
   static void *new_vectorlEbdmcLcLSharedDatalEfloatgRcLcLAlignedTgR(void *p = nullptr);
   static void *newArray_vectorlEbdmcLcLSharedDatalEfloatgRcLcLAlignedTgR(Long_t size, void *p);
   static void delete_vectorlEbdmcLcLSharedDatalEfloatgRcLcLAlignedTgR(void *p);
   static void deleteArray_vectorlEbdmcLcLSharedDatalEfloatgRcLcLAlignedTgR(void *p);
   static void destruct_vectorlEbdmcLcLSharedDatalEfloatgRcLcLAlignedTgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<bdm::SharedData<float>::AlignedT>*)
   {
      vector<bdm::SharedData<float>::AlignedT> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<bdm::SharedData<float>::AlignedT>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<bdm::SharedData<float>::AlignedT>", -2, "c++/v1/vector", 478,
                  typeid(vector<bdm::SharedData<float>::AlignedT>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEbdmcLcLSharedDatalEfloatgRcLcLAlignedTgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<bdm::SharedData<float>::AlignedT>) );
      instance.SetNew(&new_vectorlEbdmcLcLSharedDatalEfloatgRcLcLAlignedTgR);
      instance.SetNewArray(&newArray_vectorlEbdmcLcLSharedDatalEfloatgRcLcLAlignedTgR);
      instance.SetDelete(&delete_vectorlEbdmcLcLSharedDatalEfloatgRcLcLAlignedTgR);
      instance.SetDeleteArray(&deleteArray_vectorlEbdmcLcLSharedDatalEfloatgRcLcLAlignedTgR);
      instance.SetDestructor(&destruct_vectorlEbdmcLcLSharedDatalEfloatgRcLcLAlignedTgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<bdm::SharedData<float>::AlignedT> >()));

      ::ROOT::AddClassAlternate("vector<bdm::SharedData<float>::AlignedT>","std::__1::vector<bdm::SharedData<float>::AlignedT, std::__1::allocator<bdm::SharedData<float>::AlignedT>>");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<bdm::SharedData<float>::AlignedT>*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEbdmcLcLSharedDatalEfloatgRcLcLAlignedTgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<bdm::SharedData<float>::AlignedT>*)nullptr)->GetClass();
      vectorlEbdmcLcLSharedDatalEfloatgRcLcLAlignedTgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEbdmcLcLSharedDatalEfloatgRcLcLAlignedTgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEbdmcLcLSharedDatalEfloatgRcLcLAlignedTgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<bdm::SharedData<float>::AlignedT> : new vector<bdm::SharedData<float>::AlignedT>;
   }
   static void *newArray_vectorlEbdmcLcLSharedDatalEfloatgRcLcLAlignedTgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<bdm::SharedData<float>::AlignedT>[nElements] : new vector<bdm::SharedData<float>::AlignedT>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEbdmcLcLSharedDatalEfloatgRcLcLAlignedTgR(void *p) {
      delete ((vector<bdm::SharedData<float>::AlignedT>*)p);
   }
   static void deleteArray_vectorlEbdmcLcLSharedDatalEfloatgRcLcLAlignedTgR(void *p) {
      delete [] ((vector<bdm::SharedData<float>::AlignedT>*)p);
   }
   static void destruct_vectorlEbdmcLcLSharedDatalEfloatgRcLcLAlignedTgR(void *p) {
      typedef vector<bdm::SharedData<float>::AlignedT> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<bdm::SharedData<float>::AlignedT>

namespace ROOT {
   static TClass *vectorlEbdmcLcLSharedDatalEdoublegRcLcLAlignedTgR_Dictionary();
   static void vectorlEbdmcLcLSharedDatalEdoublegRcLcLAlignedTgR_TClassManip(TClass*);
   static void *new_vectorlEbdmcLcLSharedDatalEdoublegRcLcLAlignedTgR(void *p = nullptr);
   static void *newArray_vectorlEbdmcLcLSharedDatalEdoublegRcLcLAlignedTgR(Long_t size, void *p);
   static void delete_vectorlEbdmcLcLSharedDatalEdoublegRcLcLAlignedTgR(void *p);
   static void deleteArray_vectorlEbdmcLcLSharedDatalEdoublegRcLcLAlignedTgR(void *p);
   static void destruct_vectorlEbdmcLcLSharedDatalEdoublegRcLcLAlignedTgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<bdm::SharedData<double>::AlignedT>*)
   {
      vector<bdm::SharedData<double>::AlignedT> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<bdm::SharedData<double>::AlignedT>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<bdm::SharedData<double>::AlignedT>", -2, "c++/v1/vector", 478,
                  typeid(vector<bdm::SharedData<double>::AlignedT>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEbdmcLcLSharedDatalEdoublegRcLcLAlignedTgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<bdm::SharedData<double>::AlignedT>) );
      instance.SetNew(&new_vectorlEbdmcLcLSharedDatalEdoublegRcLcLAlignedTgR);
      instance.SetNewArray(&newArray_vectorlEbdmcLcLSharedDatalEdoublegRcLcLAlignedTgR);
      instance.SetDelete(&delete_vectorlEbdmcLcLSharedDatalEdoublegRcLcLAlignedTgR);
      instance.SetDeleteArray(&deleteArray_vectorlEbdmcLcLSharedDatalEdoublegRcLcLAlignedTgR);
      instance.SetDestructor(&destruct_vectorlEbdmcLcLSharedDatalEdoublegRcLcLAlignedTgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<bdm::SharedData<double>::AlignedT> >()));

      ::ROOT::AddClassAlternate("vector<bdm::SharedData<double>::AlignedT>","std::__1::vector<bdm::SharedData<double>::AlignedT, std::__1::allocator<bdm::SharedData<double>::AlignedT>>");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<bdm::SharedData<double>::AlignedT>*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEbdmcLcLSharedDatalEdoublegRcLcLAlignedTgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<bdm::SharedData<double>::AlignedT>*)nullptr)->GetClass();
      vectorlEbdmcLcLSharedDatalEdoublegRcLcLAlignedTgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEbdmcLcLSharedDatalEdoublegRcLcLAlignedTgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEbdmcLcLSharedDatalEdoublegRcLcLAlignedTgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<bdm::SharedData<double>::AlignedT> : new vector<bdm::SharedData<double>::AlignedT>;
   }
   static void *newArray_vectorlEbdmcLcLSharedDatalEdoublegRcLcLAlignedTgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<bdm::SharedData<double>::AlignedT>[nElements] : new vector<bdm::SharedData<double>::AlignedT>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEbdmcLcLSharedDatalEdoublegRcLcLAlignedTgR(void *p) {
      delete ((vector<bdm::SharedData<double>::AlignedT>*)p);
   }
   static void deleteArray_vectorlEbdmcLcLSharedDatalEdoublegRcLcLAlignedTgR(void *p) {
      delete [] ((vector<bdm::SharedData<double>::AlignedT>*)p);
   }
   static void destruct_vectorlEbdmcLcLSharedDatalEdoublegRcLcLAlignedTgR(void *p) {
      typedef vector<bdm::SharedData<double>::AlignedT> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<bdm::SharedData<double>::AlignedT>

namespace ROOT {
   static TClass *vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO4gRsPgRcLcLAlignedTgR_Dictionary();
   static void vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO4gRsPgRcLcLAlignedTgR_TClassManip(TClass*);
   static void *new_vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO4gRsPgRcLcLAlignedTgR(void *p = nullptr);
   static void *newArray_vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO4gRsPgRcLcLAlignedTgR(Long_t size, void *p);
   static void delete_vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO4gRsPgRcLcLAlignedTgR(void *p);
   static void deleteArray_vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO4gRsPgRcLcLAlignedTgR(void *p);
   static void destruct_vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO4gRsPgRcLcLAlignedTgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<bdm::SharedData<bdm::MathArray<double,4> >::AlignedT>*)
   {
      vector<bdm::SharedData<bdm::MathArray<double,4> >::AlignedT> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<bdm::SharedData<bdm::MathArray<double,4> >::AlignedT>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<bdm::SharedData<bdm::MathArray<double,4> >::AlignedT>", -2, "c++/v1/vector", 478,
                  typeid(vector<bdm::SharedData<bdm::MathArray<double,4> >::AlignedT>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO4gRsPgRcLcLAlignedTgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<bdm::SharedData<bdm::MathArray<double,4> >::AlignedT>) );
      instance.SetNew(&new_vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO4gRsPgRcLcLAlignedTgR);
      instance.SetNewArray(&newArray_vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO4gRsPgRcLcLAlignedTgR);
      instance.SetDelete(&delete_vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO4gRsPgRcLcLAlignedTgR);
      instance.SetDeleteArray(&deleteArray_vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO4gRsPgRcLcLAlignedTgR);
      instance.SetDestructor(&destruct_vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO4gRsPgRcLcLAlignedTgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<bdm::SharedData<bdm::MathArray<double,4> >::AlignedT> >()));

      ::ROOT::AddClassAlternate("vector<bdm::SharedData<bdm::MathArray<double,4> >::AlignedT>","std::__1::vector<bdm::SharedData<bdm::MathArray<double, 4ul>>::AlignedT, std::__1::allocator<bdm::SharedData<bdm::MathArray<double, 4ul>>::AlignedT>>");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<bdm::SharedData<bdm::MathArray<double,4> >::AlignedT>*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO4gRsPgRcLcLAlignedTgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<bdm::SharedData<bdm::MathArray<double,4> >::AlignedT>*)nullptr)->GetClass();
      vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO4gRsPgRcLcLAlignedTgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO4gRsPgRcLcLAlignedTgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO4gRsPgRcLcLAlignedTgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<bdm::SharedData<bdm::MathArray<double,4> >::AlignedT> : new vector<bdm::SharedData<bdm::MathArray<double,4> >::AlignedT>;
   }
   static void *newArray_vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO4gRsPgRcLcLAlignedTgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<bdm::SharedData<bdm::MathArray<double,4> >::AlignedT>[nElements] : new vector<bdm::SharedData<bdm::MathArray<double,4> >::AlignedT>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO4gRsPgRcLcLAlignedTgR(void *p) {
      delete ((vector<bdm::SharedData<bdm::MathArray<double,4> >::AlignedT>*)p);
   }
   static void deleteArray_vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO4gRsPgRcLcLAlignedTgR(void *p) {
      delete [] ((vector<bdm::SharedData<bdm::MathArray<double,4> >::AlignedT>*)p);
   }
   static void destruct_vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO4gRsPgRcLcLAlignedTgR(void *p) {
      typedef vector<bdm::SharedData<bdm::MathArray<double,4> >::AlignedT> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<bdm::SharedData<bdm::MathArray<double,4> >::AlignedT>

namespace ROOT {
   static TClass *vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO3gRsPgRcLcLAlignedTgR_Dictionary();
   static void vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO3gRsPgRcLcLAlignedTgR_TClassManip(TClass*);
   static void *new_vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO3gRsPgRcLcLAlignedTgR(void *p = nullptr);
   static void *newArray_vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO3gRsPgRcLcLAlignedTgR(Long_t size, void *p);
   static void delete_vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO3gRsPgRcLcLAlignedTgR(void *p);
   static void deleteArray_vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO3gRsPgRcLcLAlignedTgR(void *p);
   static void destruct_vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO3gRsPgRcLcLAlignedTgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<bdm::SharedData<bdm::MathArray<double,3> >::AlignedT>*)
   {
      vector<bdm::SharedData<bdm::MathArray<double,3> >::AlignedT> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<bdm::SharedData<bdm::MathArray<double,3> >::AlignedT>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<bdm::SharedData<bdm::MathArray<double,3> >::AlignedT>", -2, "c++/v1/vector", 478,
                  typeid(vector<bdm::SharedData<bdm::MathArray<double,3> >::AlignedT>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO3gRsPgRcLcLAlignedTgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<bdm::SharedData<bdm::MathArray<double,3> >::AlignedT>) );
      instance.SetNew(&new_vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO3gRsPgRcLcLAlignedTgR);
      instance.SetNewArray(&newArray_vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO3gRsPgRcLcLAlignedTgR);
      instance.SetDelete(&delete_vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO3gRsPgRcLcLAlignedTgR);
      instance.SetDeleteArray(&deleteArray_vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO3gRsPgRcLcLAlignedTgR);
      instance.SetDestructor(&destruct_vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO3gRsPgRcLcLAlignedTgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<bdm::SharedData<bdm::MathArray<double,3> >::AlignedT> >()));

      ::ROOT::AddClassAlternate("vector<bdm::SharedData<bdm::MathArray<double,3> >::AlignedT>","std::__1::vector<bdm::SharedData<bdm::MathArray<double, 3ul>>::AlignedT, std::__1::allocator<bdm::SharedData<bdm::MathArray<double, 3ul>>::AlignedT>>");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<bdm::SharedData<bdm::MathArray<double,3> >::AlignedT>*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO3gRsPgRcLcLAlignedTgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<bdm::SharedData<bdm::MathArray<double,3> >::AlignedT>*)nullptr)->GetClass();
      vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO3gRsPgRcLcLAlignedTgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO3gRsPgRcLcLAlignedTgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO3gRsPgRcLcLAlignedTgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<bdm::SharedData<bdm::MathArray<double,3> >::AlignedT> : new vector<bdm::SharedData<bdm::MathArray<double,3> >::AlignedT>;
   }
   static void *newArray_vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO3gRsPgRcLcLAlignedTgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<bdm::SharedData<bdm::MathArray<double,3> >::AlignedT>[nElements] : new vector<bdm::SharedData<bdm::MathArray<double,3> >::AlignedT>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO3gRsPgRcLcLAlignedTgR(void *p) {
      delete ((vector<bdm::SharedData<bdm::MathArray<double,3> >::AlignedT>*)p);
   }
   static void deleteArray_vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO3gRsPgRcLcLAlignedTgR(void *p) {
      delete [] ((vector<bdm::SharedData<bdm::MathArray<double,3> >::AlignedT>*)p);
   }
   static void destruct_vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO3gRsPgRcLcLAlignedTgR(void *p) {
      typedef vector<bdm::SharedData<bdm::MathArray<double,3> >::AlignedT> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<bdm::SharedData<bdm::MathArray<double,3> >::AlignedT>

namespace ROOT {
   static TClass *vectorlEbdmcLcLSharedDatalEULong64_tgRcLcLAlignedTgR_Dictionary();
   static void vectorlEbdmcLcLSharedDatalEULong64_tgRcLcLAlignedTgR_TClassManip(TClass*);
   static void *new_vectorlEbdmcLcLSharedDatalEULong64_tgRcLcLAlignedTgR(void *p = nullptr);
   static void *newArray_vectorlEbdmcLcLSharedDatalEULong64_tgRcLcLAlignedTgR(Long_t size, void *p);
   static void delete_vectorlEbdmcLcLSharedDatalEULong64_tgRcLcLAlignedTgR(void *p);
   static void deleteArray_vectorlEbdmcLcLSharedDatalEULong64_tgRcLcLAlignedTgR(void *p);
   static void destruct_vectorlEbdmcLcLSharedDatalEULong64_tgRcLcLAlignedTgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<bdm::SharedData<ULong64_t>::AlignedT>*)
   {
      vector<bdm::SharedData<ULong64_t>::AlignedT> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<bdm::SharedData<ULong64_t>::AlignedT>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<bdm::SharedData<ULong64_t>::AlignedT>", -2, "c++/v1/vector", 478,
                  typeid(vector<bdm::SharedData<ULong64_t>::AlignedT>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEbdmcLcLSharedDatalEULong64_tgRcLcLAlignedTgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<bdm::SharedData<ULong64_t>::AlignedT>) );
      instance.SetNew(&new_vectorlEbdmcLcLSharedDatalEULong64_tgRcLcLAlignedTgR);
      instance.SetNewArray(&newArray_vectorlEbdmcLcLSharedDatalEULong64_tgRcLcLAlignedTgR);
      instance.SetDelete(&delete_vectorlEbdmcLcLSharedDatalEULong64_tgRcLcLAlignedTgR);
      instance.SetDeleteArray(&deleteArray_vectorlEbdmcLcLSharedDatalEULong64_tgRcLcLAlignedTgR);
      instance.SetDestructor(&destruct_vectorlEbdmcLcLSharedDatalEULong64_tgRcLcLAlignedTgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<bdm::SharedData<ULong64_t>::AlignedT> >()));

      ::ROOT::AddClassAlternate("vector<bdm::SharedData<ULong64_t>::AlignedT>","std::__1::vector<bdm::SharedData<unsigned long long>::AlignedT, std::__1::allocator<bdm::SharedData<unsigned long long>::AlignedT>>");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<bdm::SharedData<ULong64_t>::AlignedT>*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEbdmcLcLSharedDatalEULong64_tgRcLcLAlignedTgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<bdm::SharedData<ULong64_t>::AlignedT>*)nullptr)->GetClass();
      vectorlEbdmcLcLSharedDatalEULong64_tgRcLcLAlignedTgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEbdmcLcLSharedDatalEULong64_tgRcLcLAlignedTgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEbdmcLcLSharedDatalEULong64_tgRcLcLAlignedTgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<bdm::SharedData<ULong64_t>::AlignedT> : new vector<bdm::SharedData<ULong64_t>::AlignedT>;
   }
   static void *newArray_vectorlEbdmcLcLSharedDatalEULong64_tgRcLcLAlignedTgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<bdm::SharedData<ULong64_t>::AlignedT>[nElements] : new vector<bdm::SharedData<ULong64_t>::AlignedT>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEbdmcLcLSharedDatalEULong64_tgRcLcLAlignedTgR(void *p) {
      delete ((vector<bdm::SharedData<ULong64_t>::AlignedT>*)p);
   }
   static void deleteArray_vectorlEbdmcLcLSharedDatalEULong64_tgRcLcLAlignedTgR(void *p) {
      delete [] ((vector<bdm::SharedData<ULong64_t>::AlignedT>*)p);
   }
   static void destruct_vectorlEbdmcLcLSharedDatalEULong64_tgRcLcLAlignedTgR(void *p) {
      typedef vector<bdm::SharedData<ULong64_t>::AlignedT> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<bdm::SharedData<ULong64_t>::AlignedT>

namespace ROOT {
   static TClass *vectorlEbdmcLcLRandommUgR_Dictionary();
   static void vectorlEbdmcLcLRandommUgR_TClassManip(TClass*);
   static void *new_vectorlEbdmcLcLRandommUgR(void *p = nullptr);
   static void *newArray_vectorlEbdmcLcLRandommUgR(Long_t size, void *p);
   static void delete_vectorlEbdmcLcLRandommUgR(void *p);
   static void deleteArray_vectorlEbdmcLcLRandommUgR(void *p);
   static void destruct_vectorlEbdmcLcLRandommUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<bdm::Random*>*)
   {
      vector<bdm::Random*> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<bdm::Random*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<bdm::Random*>", -2, "c++/v1/vector", 478,
                  typeid(vector<bdm::Random*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEbdmcLcLRandommUgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<bdm::Random*>) );
      instance.SetNew(&new_vectorlEbdmcLcLRandommUgR);
      instance.SetNewArray(&newArray_vectorlEbdmcLcLRandommUgR);
      instance.SetDelete(&delete_vectorlEbdmcLcLRandommUgR);
      instance.SetDeleteArray(&deleteArray_vectorlEbdmcLcLRandommUgR);
      instance.SetDestructor(&destruct_vectorlEbdmcLcLRandommUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<bdm::Random*> >()));

      ::ROOT::AddClassAlternate("vector<bdm::Random*>","std::__1::vector<bdm::Random*, std::__1::allocator<bdm::Random*>>");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<bdm::Random*>*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEbdmcLcLRandommUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<bdm::Random*>*)nullptr)->GetClass();
      vectorlEbdmcLcLRandommUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEbdmcLcLRandommUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEbdmcLcLRandommUgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<bdm::Random*> : new vector<bdm::Random*>;
   }
   static void *newArray_vectorlEbdmcLcLRandommUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<bdm::Random*>[nElements] : new vector<bdm::Random*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEbdmcLcLRandommUgR(void *p) {
      delete ((vector<bdm::Random*>*)p);
   }
   static void deleteArray_vectorlEbdmcLcLRandommUgR(void *p) {
      delete [] ((vector<bdm::Random*>*)p);
   }
   static void destruct_vectorlEbdmcLcLRandommUgR(void *p) {
      typedef vector<bdm::Random*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<bdm::Random*>

namespace ROOT {
   static TClass *vectorlEbdmcLcLParamcLcLVisualizeDiffusiongR_Dictionary();
   static void vectorlEbdmcLcLParamcLcLVisualizeDiffusiongR_TClassManip(TClass*);
   static void *new_vectorlEbdmcLcLParamcLcLVisualizeDiffusiongR(void *p = nullptr);
   static void *newArray_vectorlEbdmcLcLParamcLcLVisualizeDiffusiongR(Long_t size, void *p);
   static void delete_vectorlEbdmcLcLParamcLcLVisualizeDiffusiongR(void *p);
   static void deleteArray_vectorlEbdmcLcLParamcLcLVisualizeDiffusiongR(void *p);
   static void destruct_vectorlEbdmcLcLParamcLcLVisualizeDiffusiongR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<bdm::Param::VisualizeDiffusion>*)
   {
      vector<bdm::Param::VisualizeDiffusion> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<bdm::Param::VisualizeDiffusion>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<bdm::Param::VisualizeDiffusion>", -2, "c++/v1/vector", 478,
                  typeid(vector<bdm::Param::VisualizeDiffusion>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEbdmcLcLParamcLcLVisualizeDiffusiongR_Dictionary, isa_proxy, 4,
                  sizeof(vector<bdm::Param::VisualizeDiffusion>) );
      instance.SetNew(&new_vectorlEbdmcLcLParamcLcLVisualizeDiffusiongR);
      instance.SetNewArray(&newArray_vectorlEbdmcLcLParamcLcLVisualizeDiffusiongR);
      instance.SetDelete(&delete_vectorlEbdmcLcLParamcLcLVisualizeDiffusiongR);
      instance.SetDeleteArray(&deleteArray_vectorlEbdmcLcLParamcLcLVisualizeDiffusiongR);
      instance.SetDestructor(&destruct_vectorlEbdmcLcLParamcLcLVisualizeDiffusiongR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<bdm::Param::VisualizeDiffusion> >()));

      ::ROOT::AddClassAlternate("vector<bdm::Param::VisualizeDiffusion>","std::__1::vector<bdm::Param::VisualizeDiffusion, std::__1::allocator<bdm::Param::VisualizeDiffusion>>");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<bdm::Param::VisualizeDiffusion>*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEbdmcLcLParamcLcLVisualizeDiffusiongR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<bdm::Param::VisualizeDiffusion>*)nullptr)->GetClass();
      vectorlEbdmcLcLParamcLcLVisualizeDiffusiongR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEbdmcLcLParamcLcLVisualizeDiffusiongR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEbdmcLcLParamcLcLVisualizeDiffusiongR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<bdm::Param::VisualizeDiffusion> : new vector<bdm::Param::VisualizeDiffusion>;
   }
   static void *newArray_vectorlEbdmcLcLParamcLcLVisualizeDiffusiongR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<bdm::Param::VisualizeDiffusion>[nElements] : new vector<bdm::Param::VisualizeDiffusion>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEbdmcLcLParamcLcLVisualizeDiffusiongR(void *p) {
      delete ((vector<bdm::Param::VisualizeDiffusion>*)p);
   }
   static void deleteArray_vectorlEbdmcLcLParamcLcLVisualizeDiffusiongR(void *p) {
      delete [] ((vector<bdm::Param::VisualizeDiffusion>*)p);
   }
   static void destruct_vectorlEbdmcLcLParamcLcLVisualizeDiffusiongR(void *p) {
      typedef vector<bdm::Param::VisualizeDiffusion> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<bdm::Param::VisualizeDiffusion>

namespace ROOT {
   static TClass *vectorlEbdmcLcLOperationImplmUgR_Dictionary();
   static void vectorlEbdmcLcLOperationImplmUgR_TClassManip(TClass*);
   static void *new_vectorlEbdmcLcLOperationImplmUgR(void *p = nullptr);
   static void *newArray_vectorlEbdmcLcLOperationImplmUgR(Long_t size, void *p);
   static void delete_vectorlEbdmcLcLOperationImplmUgR(void *p);
   static void deleteArray_vectorlEbdmcLcLOperationImplmUgR(void *p);
   static void destruct_vectorlEbdmcLcLOperationImplmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<bdm::OperationImpl*>*)
   {
      vector<bdm::OperationImpl*> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<bdm::OperationImpl*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<bdm::OperationImpl*>", -2, "c++/v1/vector", 478,
                  typeid(vector<bdm::OperationImpl*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEbdmcLcLOperationImplmUgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<bdm::OperationImpl*>) );
      instance.SetNew(&new_vectorlEbdmcLcLOperationImplmUgR);
      instance.SetNewArray(&newArray_vectorlEbdmcLcLOperationImplmUgR);
      instance.SetDelete(&delete_vectorlEbdmcLcLOperationImplmUgR);
      instance.SetDeleteArray(&deleteArray_vectorlEbdmcLcLOperationImplmUgR);
      instance.SetDestructor(&destruct_vectorlEbdmcLcLOperationImplmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<bdm::OperationImpl*> >()));

      ::ROOT::AddClassAlternate("vector<bdm::OperationImpl*>","std::__1::vector<bdm::OperationImpl*, std::__1::allocator<bdm::OperationImpl*>>");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<bdm::OperationImpl*>*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEbdmcLcLOperationImplmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<bdm::OperationImpl*>*)nullptr)->GetClass();
      vectorlEbdmcLcLOperationImplmUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEbdmcLcLOperationImplmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEbdmcLcLOperationImplmUgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<bdm::OperationImpl*> : new vector<bdm::OperationImpl*>;
   }
   static void *newArray_vectorlEbdmcLcLOperationImplmUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<bdm::OperationImpl*>[nElements] : new vector<bdm::OperationImpl*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEbdmcLcLOperationImplmUgR(void *p) {
      delete ((vector<bdm::OperationImpl*>*)p);
   }
   static void deleteArray_vectorlEbdmcLcLOperationImplmUgR(void *p) {
      delete [] ((vector<bdm::OperationImpl*>*)p);
   }
   static void destruct_vectorlEbdmcLcLOperationImplmUgR(void *p) {
      typedef vector<bdm::OperationImpl*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<bdm::OperationImpl*>

namespace ROOT {
   static TClass *vectorlEbdmcLcLOperationmUgR_Dictionary();
   static void vectorlEbdmcLcLOperationmUgR_TClassManip(TClass*);
   static void *new_vectorlEbdmcLcLOperationmUgR(void *p = nullptr);
   static void *newArray_vectorlEbdmcLcLOperationmUgR(Long_t size, void *p);
   static void delete_vectorlEbdmcLcLOperationmUgR(void *p);
   static void deleteArray_vectorlEbdmcLcLOperationmUgR(void *p);
   static void destruct_vectorlEbdmcLcLOperationmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<bdm::Operation*>*)
   {
      vector<bdm::Operation*> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<bdm::Operation*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<bdm::Operation*>", -2, "c++/v1/vector", 478,
                  typeid(vector<bdm::Operation*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEbdmcLcLOperationmUgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<bdm::Operation*>) );
      instance.SetNew(&new_vectorlEbdmcLcLOperationmUgR);
      instance.SetNewArray(&newArray_vectorlEbdmcLcLOperationmUgR);
      instance.SetDelete(&delete_vectorlEbdmcLcLOperationmUgR);
      instance.SetDeleteArray(&deleteArray_vectorlEbdmcLcLOperationmUgR);
      instance.SetDestructor(&destruct_vectorlEbdmcLcLOperationmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<bdm::Operation*> >()));

      ::ROOT::AddClassAlternate("vector<bdm::Operation*>","std::__1::vector<bdm::Operation*, std::__1::allocator<bdm::Operation*>>");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<bdm::Operation*>*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEbdmcLcLOperationmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<bdm::Operation*>*)nullptr)->GetClass();
      vectorlEbdmcLcLOperationmUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEbdmcLcLOperationmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEbdmcLcLOperationmUgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<bdm::Operation*> : new vector<bdm::Operation*>;
   }
   static void *newArray_vectorlEbdmcLcLOperationmUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<bdm::Operation*>[nElements] : new vector<bdm::Operation*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEbdmcLcLOperationmUgR(void *p) {
      delete ((vector<bdm::Operation*>*)p);
   }
   static void deleteArray_vectorlEbdmcLcLOperationmUgR(void *p) {
      delete [] ((vector<bdm::Operation*>*)p);
   }
   static void destruct_vectorlEbdmcLcLOperationmUgR(void *p) {
      typedef vector<bdm::Operation*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<bdm::Operation*>

namespace ROOT {
   static TClass *vectorlEbdmcLcLMathArraylEfloatcO3gRsPgR_Dictionary();
   static void vectorlEbdmcLcLMathArraylEfloatcO3gRsPgR_TClassManip(TClass*);
   static void *new_vectorlEbdmcLcLMathArraylEfloatcO3gRsPgR(void *p = nullptr);
   static void *newArray_vectorlEbdmcLcLMathArraylEfloatcO3gRsPgR(Long_t size, void *p);
   static void delete_vectorlEbdmcLcLMathArraylEfloatcO3gRsPgR(void *p);
   static void deleteArray_vectorlEbdmcLcLMathArraylEfloatcO3gRsPgR(void *p);
   static void destruct_vectorlEbdmcLcLMathArraylEfloatcO3gRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<bdm::MathArray<float,3> >*)
   {
      vector<bdm::MathArray<float,3> > *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<bdm::MathArray<float,3> >));
      static ::ROOT::TGenericClassInfo 
         instance("vector<bdm::MathArray<float,3> >", -2, "c++/v1/vector", 478,
                  typeid(vector<bdm::MathArray<float,3> >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEbdmcLcLMathArraylEfloatcO3gRsPgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<bdm::MathArray<float,3> >) );
      instance.SetNew(&new_vectorlEbdmcLcLMathArraylEfloatcO3gRsPgR);
      instance.SetNewArray(&newArray_vectorlEbdmcLcLMathArraylEfloatcO3gRsPgR);
      instance.SetDelete(&delete_vectorlEbdmcLcLMathArraylEfloatcO3gRsPgR);
      instance.SetDeleteArray(&deleteArray_vectorlEbdmcLcLMathArraylEfloatcO3gRsPgR);
      instance.SetDestructor(&destruct_vectorlEbdmcLcLMathArraylEfloatcO3gRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<bdm::MathArray<float,3> > >()));

      ::ROOT::AddClassAlternate("vector<bdm::MathArray<float,3> >","std::__1::vector<bdm::MathArray<float, 3ul>, std::__1::allocator<bdm::MathArray<float, 3ul>>>");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<bdm::MathArray<float,3> >*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEbdmcLcLMathArraylEfloatcO3gRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<bdm::MathArray<float,3> >*)nullptr)->GetClass();
      vectorlEbdmcLcLMathArraylEfloatcO3gRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEbdmcLcLMathArraylEfloatcO3gRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEbdmcLcLMathArraylEfloatcO3gRsPgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<bdm::MathArray<float,3> > : new vector<bdm::MathArray<float,3> >;
   }
   static void *newArray_vectorlEbdmcLcLMathArraylEfloatcO3gRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<bdm::MathArray<float,3> >[nElements] : new vector<bdm::MathArray<float,3> >[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEbdmcLcLMathArraylEfloatcO3gRsPgR(void *p) {
      delete ((vector<bdm::MathArray<float,3> >*)p);
   }
   static void deleteArray_vectorlEbdmcLcLMathArraylEfloatcO3gRsPgR(void *p) {
      delete [] ((vector<bdm::MathArray<float,3> >*)p);
   }
   static void destruct_vectorlEbdmcLcLMathArraylEfloatcO3gRsPgR(void *p) {
      typedef vector<bdm::MathArray<float,3> > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<bdm::MathArray<float,3> >

namespace ROOT {
   static TClass *vectorlEbdmcLcLFunctorlEboolcObdmcLcLAgentmUgRmUgR_Dictionary();
   static void vectorlEbdmcLcLFunctorlEboolcObdmcLcLAgentmUgRmUgR_TClassManip(TClass*);
   static void *new_vectorlEbdmcLcLFunctorlEboolcObdmcLcLAgentmUgRmUgR(void *p = nullptr);
   static void *newArray_vectorlEbdmcLcLFunctorlEboolcObdmcLcLAgentmUgRmUgR(Long_t size, void *p);
   static void delete_vectorlEbdmcLcLFunctorlEboolcObdmcLcLAgentmUgRmUgR(void *p);
   static void deleteArray_vectorlEbdmcLcLFunctorlEboolcObdmcLcLAgentmUgRmUgR(void *p);
   static void destruct_vectorlEbdmcLcLFunctorlEboolcObdmcLcLAgentmUgRmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<bdm::Functor<bool,bdm::Agent*>*>*)
   {
      vector<bdm::Functor<bool,bdm::Agent*>*> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<bdm::Functor<bool,bdm::Agent*>*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<bdm::Functor<bool,bdm::Agent*>*>", -2, "c++/v1/vector", 478,
                  typeid(vector<bdm::Functor<bool,bdm::Agent*>*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEbdmcLcLFunctorlEboolcObdmcLcLAgentmUgRmUgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<bdm::Functor<bool,bdm::Agent*>*>) );
      instance.SetNew(&new_vectorlEbdmcLcLFunctorlEboolcObdmcLcLAgentmUgRmUgR);
      instance.SetNewArray(&newArray_vectorlEbdmcLcLFunctorlEboolcObdmcLcLAgentmUgRmUgR);
      instance.SetDelete(&delete_vectorlEbdmcLcLFunctorlEboolcObdmcLcLAgentmUgRmUgR);
      instance.SetDeleteArray(&deleteArray_vectorlEbdmcLcLFunctorlEboolcObdmcLcLAgentmUgRmUgR);
      instance.SetDestructor(&destruct_vectorlEbdmcLcLFunctorlEboolcObdmcLcLAgentmUgRmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<bdm::Functor<bool,bdm::Agent*>*> >()));

      ::ROOT::AddClassAlternate("vector<bdm::Functor<bool,bdm::Agent*>*>","std::__1::vector<bdm::Functor<bool, bdm::Agent*>*, std::__1::allocator<bdm::Functor<bool, bdm::Agent*>*>>");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<bdm::Functor<bool,bdm::Agent*>*>*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEbdmcLcLFunctorlEboolcObdmcLcLAgentmUgRmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<bdm::Functor<bool,bdm::Agent*>*>*)nullptr)->GetClass();
      vectorlEbdmcLcLFunctorlEboolcObdmcLcLAgentmUgRmUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEbdmcLcLFunctorlEboolcObdmcLcLAgentmUgRmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEbdmcLcLFunctorlEboolcObdmcLcLAgentmUgRmUgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<bdm::Functor<bool,bdm::Agent*>*> : new vector<bdm::Functor<bool,bdm::Agent*>*>;
   }
   static void *newArray_vectorlEbdmcLcLFunctorlEboolcObdmcLcLAgentmUgRmUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<bdm::Functor<bool,bdm::Agent*>*>[nElements] : new vector<bdm::Functor<bool,bdm::Agent*>*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEbdmcLcLFunctorlEboolcObdmcLcLAgentmUgRmUgR(void *p) {
      delete ((vector<bdm::Functor<bool,bdm::Agent*>*>*)p);
   }
   static void deleteArray_vectorlEbdmcLcLFunctorlEboolcObdmcLcLAgentmUgRmUgR(void *p) {
      delete [] ((vector<bdm::Functor<bool,bdm::Agent*>*>*)p);
   }
   static void destruct_vectorlEbdmcLcLFunctorlEboolcObdmcLcLAgentmUgRmUgR(void *p) {
      typedef vector<bdm::Functor<bool,bdm::Agent*>*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<bdm::Functor<bool,bdm::Agent*>*>

namespace ROOT {
   static TClass *vectorlEbdmcLcLExecutionContextmUgR_Dictionary();
   static void vectorlEbdmcLcLExecutionContextmUgR_TClassManip(TClass*);
   static void *new_vectorlEbdmcLcLExecutionContextmUgR(void *p = nullptr);
   static void *newArray_vectorlEbdmcLcLExecutionContextmUgR(Long_t size, void *p);
   static void delete_vectorlEbdmcLcLExecutionContextmUgR(void *p);
   static void deleteArray_vectorlEbdmcLcLExecutionContextmUgR(void *p);
   static void destruct_vectorlEbdmcLcLExecutionContextmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<bdm::ExecutionContext*>*)
   {
      vector<bdm::ExecutionContext*> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<bdm::ExecutionContext*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<bdm::ExecutionContext*>", -2, "c++/v1/vector", 478,
                  typeid(vector<bdm::ExecutionContext*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEbdmcLcLExecutionContextmUgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<bdm::ExecutionContext*>) );
      instance.SetNew(&new_vectorlEbdmcLcLExecutionContextmUgR);
      instance.SetNewArray(&newArray_vectorlEbdmcLcLExecutionContextmUgR);
      instance.SetDelete(&delete_vectorlEbdmcLcLExecutionContextmUgR);
      instance.SetDeleteArray(&deleteArray_vectorlEbdmcLcLExecutionContextmUgR);
      instance.SetDestructor(&destruct_vectorlEbdmcLcLExecutionContextmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<bdm::ExecutionContext*> >()));

      ::ROOT::AddClassAlternate("vector<bdm::ExecutionContext*>","std::__1::vector<bdm::ExecutionContext*, std::__1::allocator<bdm::ExecutionContext*>>");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<bdm::ExecutionContext*>*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEbdmcLcLExecutionContextmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<bdm::ExecutionContext*>*)nullptr)->GetClass();
      vectorlEbdmcLcLExecutionContextmUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEbdmcLcLExecutionContextmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEbdmcLcLExecutionContextmUgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<bdm::ExecutionContext*> : new vector<bdm::ExecutionContext*>;
   }
   static void *newArray_vectorlEbdmcLcLExecutionContextmUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<bdm::ExecutionContext*>[nElements] : new vector<bdm::ExecutionContext*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEbdmcLcLExecutionContextmUgR(void *p) {
      delete ((vector<bdm::ExecutionContext*>*)p);
   }
   static void deleteArray_vectorlEbdmcLcLExecutionContextmUgR(void *p) {
      delete [] ((vector<bdm::ExecutionContext*>*)p);
   }
   static void destruct_vectorlEbdmcLcLExecutionContextmUgR(void *p) {
      typedef vector<bdm::ExecutionContext*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<bdm::ExecutionContext*>

namespace ROOT {
   static TClass *vectorlEbdmcLcLBehaviormUgR_Dictionary();
   static void vectorlEbdmcLcLBehaviormUgR_TClassManip(TClass*);
   static void *new_vectorlEbdmcLcLBehaviormUgR(void *p = nullptr);
   static void *newArray_vectorlEbdmcLcLBehaviormUgR(Long_t size, void *p);
   static void delete_vectorlEbdmcLcLBehaviormUgR(void *p);
   static void deleteArray_vectorlEbdmcLcLBehaviormUgR(void *p);
   static void destruct_vectorlEbdmcLcLBehaviormUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<bdm::Behavior*>*)
   {
      vector<bdm::Behavior*> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<bdm::Behavior*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<bdm::Behavior*>", -2, "c++/v1/vector", 478,
                  typeid(vector<bdm::Behavior*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEbdmcLcLBehaviormUgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<bdm::Behavior*>) );
      instance.SetNew(&new_vectorlEbdmcLcLBehaviormUgR);
      instance.SetNewArray(&newArray_vectorlEbdmcLcLBehaviormUgR);
      instance.SetDelete(&delete_vectorlEbdmcLcLBehaviormUgR);
      instance.SetDeleteArray(&deleteArray_vectorlEbdmcLcLBehaviormUgR);
      instance.SetDestructor(&destruct_vectorlEbdmcLcLBehaviormUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<bdm::Behavior*> >()));

      ::ROOT::AddClassAlternate("vector<bdm::Behavior*>","std::__1::vector<bdm::Behavior*, std::__1::allocator<bdm::Behavior*>>");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<bdm::Behavior*>*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEbdmcLcLBehaviormUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<bdm::Behavior*>*)nullptr)->GetClass();
      vectorlEbdmcLcLBehaviormUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEbdmcLcLBehaviormUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEbdmcLcLBehaviormUgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<bdm::Behavior*> : new vector<bdm::Behavior*>;
   }
   static void *newArray_vectorlEbdmcLcLBehaviormUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<bdm::Behavior*>[nElements] : new vector<bdm::Behavior*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEbdmcLcLBehaviormUgR(void *p) {
      delete ((vector<bdm::Behavior*>*)p);
   }
   static void deleteArray_vectorlEbdmcLcLBehaviormUgR(void *p) {
      delete [] ((vector<bdm::Behavior*>*)p);
   }
   static void destruct_vectorlEbdmcLcLBehaviormUgR(void *p) {
      typedef vector<bdm::Behavior*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<bdm::Behavior*>

namespace ROOT {
   static TClass *vectorlEbdmcLcLAgentUidgR_Dictionary();
   static void vectorlEbdmcLcLAgentUidgR_TClassManip(TClass*);
   static void *new_vectorlEbdmcLcLAgentUidgR(void *p = nullptr);
   static void *newArray_vectorlEbdmcLcLAgentUidgR(Long_t size, void *p);
   static void delete_vectorlEbdmcLcLAgentUidgR(void *p);
   static void deleteArray_vectorlEbdmcLcLAgentUidgR(void *p);
   static void destruct_vectorlEbdmcLcLAgentUidgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<bdm::AgentUid>*)
   {
      vector<bdm::AgentUid> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<bdm::AgentUid>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<bdm::AgentUid>", -2, "c++/v1/vector", 478,
                  typeid(vector<bdm::AgentUid>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEbdmcLcLAgentUidgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<bdm::AgentUid>) );
      instance.SetNew(&new_vectorlEbdmcLcLAgentUidgR);
      instance.SetNewArray(&newArray_vectorlEbdmcLcLAgentUidgR);
      instance.SetDelete(&delete_vectorlEbdmcLcLAgentUidgR);
      instance.SetDeleteArray(&deleteArray_vectorlEbdmcLcLAgentUidgR);
      instance.SetDestructor(&destruct_vectorlEbdmcLcLAgentUidgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<bdm::AgentUid> >()));

      ::ROOT::AddClassAlternate("vector<bdm::AgentUid>","std::__1::vector<bdm::AgentUid, std::__1::allocator<bdm::AgentUid>>");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<bdm::AgentUid>*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEbdmcLcLAgentUidgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<bdm::AgentUid>*)nullptr)->GetClass();
      vectorlEbdmcLcLAgentUidgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEbdmcLcLAgentUidgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEbdmcLcLAgentUidgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<bdm::AgentUid> : new vector<bdm::AgentUid>;
   }
   static void *newArray_vectorlEbdmcLcLAgentUidgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<bdm::AgentUid>[nElements] : new vector<bdm::AgentUid>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEbdmcLcLAgentUidgR(void *p) {
      delete ((vector<bdm::AgentUid>*)p);
   }
   static void deleteArray_vectorlEbdmcLcLAgentUidgR(void *p) {
      delete [] ((vector<bdm::AgentUid>*)p);
   }
   static void destruct_vectorlEbdmcLcLAgentUidgR(void *p) {
      typedef vector<bdm::AgentUid> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<bdm::AgentUid>

namespace ROOT {
   static TClass *vectorlEbdmcLcLAgentPointerlEbdmcLcLneurosciencecLcLNeuriteElementgRsPgR_Dictionary();
   static void vectorlEbdmcLcLAgentPointerlEbdmcLcLneurosciencecLcLNeuriteElementgRsPgR_TClassManip(TClass*);
   static void *new_vectorlEbdmcLcLAgentPointerlEbdmcLcLneurosciencecLcLNeuriteElementgRsPgR(void *p = nullptr);
   static void *newArray_vectorlEbdmcLcLAgentPointerlEbdmcLcLneurosciencecLcLNeuriteElementgRsPgR(Long_t size, void *p);
   static void delete_vectorlEbdmcLcLAgentPointerlEbdmcLcLneurosciencecLcLNeuriteElementgRsPgR(void *p);
   static void deleteArray_vectorlEbdmcLcLAgentPointerlEbdmcLcLneurosciencecLcLNeuriteElementgRsPgR(void *p);
   static void destruct_vectorlEbdmcLcLAgentPointerlEbdmcLcLneurosciencecLcLNeuriteElementgRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<bdm::AgentPointer<bdm::neuroscience::NeuriteElement> >*)
   {
      vector<bdm::AgentPointer<bdm::neuroscience::NeuriteElement> > *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<bdm::AgentPointer<bdm::neuroscience::NeuriteElement> >));
      static ::ROOT::TGenericClassInfo 
         instance("vector<bdm::AgentPointer<bdm::neuroscience::NeuriteElement> >", -2, "c++/v1/vector", 478,
                  typeid(vector<bdm::AgentPointer<bdm::neuroscience::NeuriteElement> >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEbdmcLcLAgentPointerlEbdmcLcLneurosciencecLcLNeuriteElementgRsPgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<bdm::AgentPointer<bdm::neuroscience::NeuriteElement> >) );
      instance.SetNew(&new_vectorlEbdmcLcLAgentPointerlEbdmcLcLneurosciencecLcLNeuriteElementgRsPgR);
      instance.SetNewArray(&newArray_vectorlEbdmcLcLAgentPointerlEbdmcLcLneurosciencecLcLNeuriteElementgRsPgR);
      instance.SetDelete(&delete_vectorlEbdmcLcLAgentPointerlEbdmcLcLneurosciencecLcLNeuriteElementgRsPgR);
      instance.SetDeleteArray(&deleteArray_vectorlEbdmcLcLAgentPointerlEbdmcLcLneurosciencecLcLNeuriteElementgRsPgR);
      instance.SetDestructor(&destruct_vectorlEbdmcLcLAgentPointerlEbdmcLcLneurosciencecLcLNeuriteElementgRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<bdm::AgentPointer<bdm::neuroscience::NeuriteElement> > >()));

      ::ROOT::AddClassAlternate("vector<bdm::AgentPointer<bdm::neuroscience::NeuriteElement> >","std::__1::vector<bdm::AgentPointer<bdm::neuroscience::NeuriteElement>, std::__1::allocator<bdm::AgentPointer<bdm::neuroscience::NeuriteElement>>>");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<bdm::AgentPointer<bdm::neuroscience::NeuriteElement> >*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEbdmcLcLAgentPointerlEbdmcLcLneurosciencecLcLNeuriteElementgRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<bdm::AgentPointer<bdm::neuroscience::NeuriteElement> >*)nullptr)->GetClass();
      vectorlEbdmcLcLAgentPointerlEbdmcLcLneurosciencecLcLNeuriteElementgRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEbdmcLcLAgentPointerlEbdmcLcLneurosciencecLcLNeuriteElementgRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEbdmcLcLAgentPointerlEbdmcLcLneurosciencecLcLNeuriteElementgRsPgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<bdm::AgentPointer<bdm::neuroscience::NeuriteElement> > : new vector<bdm::AgentPointer<bdm::neuroscience::NeuriteElement> >;
   }
   static void *newArray_vectorlEbdmcLcLAgentPointerlEbdmcLcLneurosciencecLcLNeuriteElementgRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<bdm::AgentPointer<bdm::neuroscience::NeuriteElement> >[nElements] : new vector<bdm::AgentPointer<bdm::neuroscience::NeuriteElement> >[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEbdmcLcLAgentPointerlEbdmcLcLneurosciencecLcLNeuriteElementgRsPgR(void *p) {
      delete ((vector<bdm::AgentPointer<bdm::neuroscience::NeuriteElement> >*)p);
   }
   static void deleteArray_vectorlEbdmcLcLAgentPointerlEbdmcLcLneurosciencecLcLNeuriteElementgRsPgR(void *p) {
      delete [] ((vector<bdm::AgentPointer<bdm::neuroscience::NeuriteElement> >*)p);
   }
   static void destruct_vectorlEbdmcLcLAgentPointerlEbdmcLcLneurosciencecLcLNeuriteElementgRsPgR(void *p) {
      typedef vector<bdm::AgentPointer<bdm::neuroscience::NeuriteElement> > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<bdm::AgentPointer<bdm::neuroscience::NeuriteElement> >

namespace ROOT {
   static TClass *vectorlEbdmcLcLAgentPointerlEbdmcLcLAgentgRsPgR_Dictionary();
   static void vectorlEbdmcLcLAgentPointerlEbdmcLcLAgentgRsPgR_TClassManip(TClass*);
   static void *new_vectorlEbdmcLcLAgentPointerlEbdmcLcLAgentgRsPgR(void *p = nullptr);
   static void *newArray_vectorlEbdmcLcLAgentPointerlEbdmcLcLAgentgRsPgR(Long_t size, void *p);
   static void delete_vectorlEbdmcLcLAgentPointerlEbdmcLcLAgentgRsPgR(void *p);
   static void deleteArray_vectorlEbdmcLcLAgentPointerlEbdmcLcLAgentgRsPgR(void *p);
   static void destruct_vectorlEbdmcLcLAgentPointerlEbdmcLcLAgentgRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<bdm::AgentPointer<bdm::Agent> >*)
   {
      vector<bdm::AgentPointer<bdm::Agent> > *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<bdm::AgentPointer<bdm::Agent> >));
      static ::ROOT::TGenericClassInfo 
         instance("vector<bdm::AgentPointer<bdm::Agent> >", -2, "c++/v1/vector", 478,
                  typeid(vector<bdm::AgentPointer<bdm::Agent> >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEbdmcLcLAgentPointerlEbdmcLcLAgentgRsPgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<bdm::AgentPointer<bdm::Agent> >) );
      instance.SetNew(&new_vectorlEbdmcLcLAgentPointerlEbdmcLcLAgentgRsPgR);
      instance.SetNewArray(&newArray_vectorlEbdmcLcLAgentPointerlEbdmcLcLAgentgRsPgR);
      instance.SetDelete(&delete_vectorlEbdmcLcLAgentPointerlEbdmcLcLAgentgRsPgR);
      instance.SetDeleteArray(&deleteArray_vectorlEbdmcLcLAgentPointerlEbdmcLcLAgentgRsPgR);
      instance.SetDestructor(&destruct_vectorlEbdmcLcLAgentPointerlEbdmcLcLAgentgRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<bdm::AgentPointer<bdm::Agent> > >()));

      ::ROOT::AddClassAlternate("vector<bdm::AgentPointer<bdm::Agent> >","std::__1::vector<bdm::AgentPointer<bdm::Agent>, std::__1::allocator<bdm::AgentPointer<bdm::Agent>>>");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<bdm::AgentPointer<bdm::Agent> >*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEbdmcLcLAgentPointerlEbdmcLcLAgentgRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<bdm::AgentPointer<bdm::Agent> >*)nullptr)->GetClass();
      vectorlEbdmcLcLAgentPointerlEbdmcLcLAgentgRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEbdmcLcLAgentPointerlEbdmcLcLAgentgRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEbdmcLcLAgentPointerlEbdmcLcLAgentgRsPgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<bdm::AgentPointer<bdm::Agent> > : new vector<bdm::AgentPointer<bdm::Agent> >;
   }
   static void *newArray_vectorlEbdmcLcLAgentPointerlEbdmcLcLAgentgRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<bdm::AgentPointer<bdm::Agent> >[nElements] : new vector<bdm::AgentPointer<bdm::Agent> >[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEbdmcLcLAgentPointerlEbdmcLcLAgentgRsPgR(void *p) {
      delete ((vector<bdm::AgentPointer<bdm::Agent> >*)p);
   }
   static void deleteArray_vectorlEbdmcLcLAgentPointerlEbdmcLcLAgentgRsPgR(void *p) {
      delete [] ((vector<bdm::AgentPointer<bdm::Agent> >*)p);
   }
   static void destruct_vectorlEbdmcLcLAgentPointerlEbdmcLcLAgentgRsPgR(void *p) {
      typedef vector<bdm::AgentPointer<bdm::Agent> > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<bdm::AgentPointer<bdm::Agent> >

namespace ROOT {
   static TClass *vectorlEbdmcLcLAgentHandlegR_Dictionary();
   static void vectorlEbdmcLcLAgentHandlegR_TClassManip(TClass*);
   static void *new_vectorlEbdmcLcLAgentHandlegR(void *p = nullptr);
   static void *newArray_vectorlEbdmcLcLAgentHandlegR(Long_t size, void *p);
   static void delete_vectorlEbdmcLcLAgentHandlegR(void *p);
   static void deleteArray_vectorlEbdmcLcLAgentHandlegR(void *p);
   static void destruct_vectorlEbdmcLcLAgentHandlegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<bdm::AgentHandle>*)
   {
      vector<bdm::AgentHandle> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<bdm::AgentHandle>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<bdm::AgentHandle>", -2, "c++/v1/vector", 478,
                  typeid(vector<bdm::AgentHandle>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEbdmcLcLAgentHandlegR_Dictionary, isa_proxy, 4,
                  sizeof(vector<bdm::AgentHandle>) );
      instance.SetNew(&new_vectorlEbdmcLcLAgentHandlegR);
      instance.SetNewArray(&newArray_vectorlEbdmcLcLAgentHandlegR);
      instance.SetDelete(&delete_vectorlEbdmcLcLAgentHandlegR);
      instance.SetDeleteArray(&deleteArray_vectorlEbdmcLcLAgentHandlegR);
      instance.SetDestructor(&destruct_vectorlEbdmcLcLAgentHandlegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<bdm::AgentHandle> >()));

      ::ROOT::AddClassAlternate("vector<bdm::AgentHandle>","std::__1::vector<bdm::AgentHandle, std::__1::allocator<bdm::AgentHandle>>");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<bdm::AgentHandle>*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEbdmcLcLAgentHandlegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<bdm::AgentHandle>*)nullptr)->GetClass();
      vectorlEbdmcLcLAgentHandlegR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEbdmcLcLAgentHandlegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEbdmcLcLAgentHandlegR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<bdm::AgentHandle> : new vector<bdm::AgentHandle>;
   }
   static void *newArray_vectorlEbdmcLcLAgentHandlegR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<bdm::AgentHandle>[nElements] : new vector<bdm::AgentHandle>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEbdmcLcLAgentHandlegR(void *p) {
      delete ((vector<bdm::AgentHandle>*)p);
   }
   static void deleteArray_vectorlEbdmcLcLAgentHandlegR(void *p) {
      delete [] ((vector<bdm::AgentHandle>*)p);
   }
   static void destruct_vectorlEbdmcLcLAgentHandlegR(void *p) {
      typedef vector<bdm::AgentHandle> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<bdm::AgentHandle>

namespace ROOT {
   static TClass *vectorlEbdmcLcLAgentmUgR_Dictionary();
   static void vectorlEbdmcLcLAgentmUgR_TClassManip(TClass*);
   static void *new_vectorlEbdmcLcLAgentmUgR(void *p = nullptr);
   static void *newArray_vectorlEbdmcLcLAgentmUgR(Long_t size, void *p);
   static void delete_vectorlEbdmcLcLAgentmUgR(void *p);
   static void deleteArray_vectorlEbdmcLcLAgentmUgR(void *p);
   static void destruct_vectorlEbdmcLcLAgentmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<bdm::Agent*>*)
   {
      vector<bdm::Agent*> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<bdm::Agent*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<bdm::Agent*>", -2, "c++/v1/vector", 478,
                  typeid(vector<bdm::Agent*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEbdmcLcLAgentmUgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<bdm::Agent*>) );
      instance.SetNew(&new_vectorlEbdmcLcLAgentmUgR);
      instance.SetNewArray(&newArray_vectorlEbdmcLcLAgentmUgR);
      instance.SetDelete(&delete_vectorlEbdmcLcLAgentmUgR);
      instance.SetDeleteArray(&deleteArray_vectorlEbdmcLcLAgentmUgR);
      instance.SetDestructor(&destruct_vectorlEbdmcLcLAgentmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<bdm::Agent*> >()));

      ::ROOT::AddClassAlternate("vector<bdm::Agent*>","std::__1::vector<bdm::Agent*, std::__1::allocator<bdm::Agent*>>");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<bdm::Agent*>*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEbdmcLcLAgentmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<bdm::Agent*>*)nullptr)->GetClass();
      vectorlEbdmcLcLAgentmUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEbdmcLcLAgentmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEbdmcLcLAgentmUgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<bdm::Agent*> : new vector<bdm::Agent*>;
   }
   static void *newArray_vectorlEbdmcLcLAgentmUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<bdm::Agent*>[nElements] : new vector<bdm::Agent*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEbdmcLcLAgentmUgR(void *p) {
      delete ((vector<bdm::Agent*>*)p);
   }
   static void deleteArray_vectorlEbdmcLcLAgentmUgR(void *p) {
      delete [] ((vector<bdm::Agent*>*)p);
   }
   static void destruct_vectorlEbdmcLcLAgentmUgR(void *p) {
      typedef vector<bdm::Agent*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<bdm::Agent*>

namespace ROOT {
   static TClass *vectorlEarraylEfloatcO8gRsPgR_Dictionary();
   static void vectorlEarraylEfloatcO8gRsPgR_TClassManip(TClass*);
   static void *new_vectorlEarraylEfloatcO8gRsPgR(void *p = nullptr);
   static void *newArray_vectorlEarraylEfloatcO8gRsPgR(Long_t size, void *p);
   static void delete_vectorlEarraylEfloatcO8gRsPgR(void *p);
   static void deleteArray_vectorlEarraylEfloatcO8gRsPgR(void *p);
   static void destruct_vectorlEarraylEfloatcO8gRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<array<float,8> >*)
   {
      vector<array<float,8> > *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<array<float,8> >));
      static ::ROOT::TGenericClassInfo 
         instance("vector<array<float,8> >", -2, "c++/v1/vector", 478,
                  typeid(vector<array<float,8> >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEarraylEfloatcO8gRsPgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<array<float,8> >) );
      instance.SetNew(&new_vectorlEarraylEfloatcO8gRsPgR);
      instance.SetNewArray(&newArray_vectorlEarraylEfloatcO8gRsPgR);
      instance.SetDelete(&delete_vectorlEarraylEfloatcO8gRsPgR);
      instance.SetDeleteArray(&deleteArray_vectorlEarraylEfloatcO8gRsPgR);
      instance.SetDestructor(&destruct_vectorlEarraylEfloatcO8gRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<array<float,8> > >()));

      ::ROOT::AddClassAlternate("vector<array<float,8> >","std::__1::vector<std::__1::array<float, 8ul>, std::__1::allocator<std::__1::array<float, 8ul>>>");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<array<float,8> >*)nullptr); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEarraylEfloatcO8gRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<array<float,8> >*)nullptr)->GetClass();
      vectorlEarraylEfloatcO8gRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEarraylEfloatcO8gRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEarraylEfloatcO8gRsPgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<array<float,8> > : new vector<array<float,8> >;
   }
   static void *newArray_vectorlEarraylEfloatcO8gRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<array<float,8> >[nElements] : new vector<array<float,8> >[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEarraylEfloatcO8gRsPgR(void *p) {
      delete ((vector<array<float,8> >*)p);
   }
   static void deleteArray_vectorlEarraylEfloatcO8gRsPgR(void *p) {
      delete [] ((vector<array<float,8> >*)p);
   }
   static void destruct_vectorlEarraylEfloatcO8gRsPgR(void *p) {
      typedef vector<array<float,8> > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<array<float,8> >

namespace {
  void TriggerDictionaryInitialization_libunitmItestmImechanics_dict_Impl() {
    static const char* headers[] = {
"0",
nullptr
    };
    static const char* includePaths[] = {
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "libunitmItestmImechanics_dict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
namespace bdm{struct __attribute__((annotate("$clingAutoload$core/operation/operation.h")))  __attribute__((annotate("$clingAutoload$biodynamo.h")))  OperationImpl;}
namespace std{inline namespace __1{template <class _Tp> class __attribute__((annotate("$clingAutoload$iosfwd")))  __attribute__((annotate("$clingAutoload$string")))  allocator;
}}
namespace bdm{class __attribute__((annotate("$clingAutoload$core/execution_context/execution_context.h")))  __attribute__((annotate("$clingAutoload$biodynamo.h")))  ExecutionContext;}
namespace bdm{struct __attribute__((annotate("$clingAutoload$core/operation/operation.h")))  __attribute__((annotate("$clingAutoload$biodynamo.h")))  Operation;}
namespace bdm{class __attribute__((annotate("$clingAutoload$core/util/random.h")))  __attribute__((annotate("$clingAutoload$biodynamo.h")))  Random;}
namespace bdm{class __attribute__((annotate("$clingAutoload$core/agent/agent.h")))  __attribute__((annotate("$clingAutoload$biodynamo.h")))  Agent;}
namespace bdm{class __attribute__((annotate("$clingAutoload$core/behavior/behavior.h")))  __attribute__((annotate("$clingAutoload$biodynamo.h")))  Behavior;}
namespace bdm{template <typename TAgent = bdm::Agent> class __attribute__((annotate("$clingAutoload$core/agent/agent_pointer.h")))  __attribute__((annotate("$clingAutoload$biodynamo.h")))  AgentPointer;
}
namespace bdm{class __attribute__((annotate("$clingAutoload$core/agent/agent_uid.h")))  __attribute__((annotate("$clingAutoload$biodynamo.h")))  AgentUid;}
namespace bdm{class __attribute__((annotate("$clingAutoload$core/util/spinlock.h")))  __attribute__((annotate("$clingAutoload$biodynamo.h")))  Spinlock;}
namespace bdm{template <typename TReturn, typename ...TArgs> class __attribute__((annotate("$clingAutoload$core/functor.h")))  __attribute__((annotate("$clingAutoload$biodynamo.h")))  Functor;
}
namespace bdm{class __attribute__((annotate("$clingAutoload$core/agent/agent_handle.h")))  __attribute__((annotate("$clingAutoload$biodynamo.h")))  AgentHandle;}
namespace bdm{namespace neuroscience{class __attribute__((annotate("$clingAutoload$neuroscience/neurite_element.h")))  __attribute__((annotate("$clingAutoload$biodynamo.h")))  NeuriteElement;}}
namespace bdm{template <typename T> class __attribute__((annotate("$clingAutoload$core/container/shared_data.h")))  __attribute__((annotate("$clingAutoload$biodynamo.h")))  SharedData;
}
namespace bdm{class __attribute__((annotate(R"ATTRDUMP(pattern@@@bdm::*)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$core/util/progress_bar.h")))  __attribute__((annotate("$clingAutoload$biodynamo.h")))  ProgressBar;}
namespace bdm{class __attribute__((annotate(R"ATTRDUMP(pattern@@@bdm::*)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$core/diffusion/continuum_interface.h")))  __attribute__((annotate("$clingAutoload$biodynamo.h")))  VectorField;}
namespace bdm{class __attribute__((annotate(R"ATTRDUMP(pattern@@@bdm::*)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$moving_cell.h")))  Moving_cell;}
namespace bdm{struct __attribute__((annotate(R"ATTRDUMP(pattern@@@bdm::*)ATTRDUMP"))) DissipativeForce;}
namespace bdm{struct __attribute__((annotate(R"ATTRDUMP(pattern@@@bdm::*)ATTRDUMP"))) ApplyForce;}
namespace bdm{struct __attribute__((annotate(R"ATTRDUMP(pattern@@@bdm::*)ATTRDUMP"))) TrackPosition;}
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "libunitmItestmImechanics_dict dictionary payload"

#ifndef BDM_REALT
  #define BDM_REALT float
#endif
#ifndef BDMSYS
  #define BDMSYS /Users/hp024/biodynamo/build
#endif
#ifndef USE_MPI
  #define USE_MPI 1
#endif
#ifndef USE_DICT
  #define USE_DICT 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#ifndef CUSTOM_OPS_H_
#define CUSTOM_OPS_H_

#include "biodynamo.h"
#include "moving_cell.h"

namespace bdm {

struct DissipativeForce : public AgentOperationImpl {
  BDM_OP_HEADER(DissipativeForce);

  void operator()(Agent* agent) override {
    if (auto* cell = bdm_static_cast<Moving_cell*>(agent)) {
      Real3 decrease_speed = cell->GetSpeed() * (-friction_coefficient_);

      cell->UpdateSpeed(decrease_speed);
    }
  }

  double friction_coefficient_ = 0.;
};

struct ApplyForce : public AgentOperationImpl {
  BDM_OP_HEADER(ApplyForce);

  void operator()(Agent* agent) override {
    if (auto* cell = bdm_static_cast<Moving_cell*>(agent)) {
      real_t dt = Simulation::GetActive()->GetParam()->simulation_time_step;
      Real3 displacement = initial_speed_ * dt;

      std::cout << "initial speed: " << initial_speed_ << ", dt " << dt << std::endl;

      cell->ApplyDisplacement(displacement);
    }
  }

  Real3 initial_speed_ = {0., 0., 0.};
};

struct TrackPosition : public AgentOperationImpl {
  BDM_OP_HEADER(TrackPosition);

  // GetUid()

  void operator()(Agent* agent) override {
    (*positions_).push_back(agent->GetPosition());
  }

  std::vector<Real3>* positions_;
};

}  // namespace bdm

#endif
#ifndef MOVING_CELL_H_
#define MOVING_CELL_H_

#include "biodynamo.h"
#include "core/agent/cell.h"

namespace bdm {

class Moving_cell : public Cell {
  BDM_AGENT_HEADER(Moving_cell, Cell, 1);

 public:
  Moving_cell() {}
  explicit Moving_cell(const Real3& position) : Base(position) {}
  virtual ~Moving_cell() {}

  Real3 GetSpeed() { return speed_; }

  void SetSpeed(Real3 speed) { speed_ = speed; }

  void UpdateSpeed(Real3 delta_speed) {
    speed_ += delta_speed;
  }

 private:
  // 10 um/min -> 1um/0.1 min
  Real3 speed_ = {0.0, 0.0, 0.0};
};

}  // namespace bdm

#endif  // MOVING_CELL_H_// -----------------------------------------------------------------------------
//
// Copyright (C) 2021 CERN & University of Surrey for the benefit of the
// BioDynaMo collaboration. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
//
// See the LICENSE file distributed with this work for details.
// See the NOTICE file distributed with this work for additional information
// regarding copyright ownership.
//
// -----------------------------------------------------------------------------
#ifndef UNIT_TEST_MECHANICS_H_
#define UNIT_TEST_MECHANICS_H_

#include "biodynamo.h"
#include "custom_ops.h"
#include "moving_cell.h"

namespace bdm {

inline int Simulate(int argc, const char** argv) {
  auto set_param = [](auto* param) {
    // Closed domain, 27 voxel (3x3x3), voxel size = 20um per side
    param->bound_space = Param::BoundSpaceMode::kClosed;
    param->min_bound = -30;
    param->max_bound = 30;
    param->statistics = true;
    param->simulation_time_step = 0.1;  // 0.1 minutes
    param->diffusion_boundary_condition = "closed";
  };

  Simulation simulation(argc, argv, set_param);
  auto *scheduler = simulation.GetScheduler();

  double const cell_diameter = 10.;  // um
  double const PI = 3.14159265;
  double const cell_volume = 4. / 3. * PI * pow(cell_diameter / 2., 3);  // um^3
  double const cell_density = pow(10, -15);  // 1kg/m^3 = 10^-15g/um^3
  double const cell_mass = cell_volume * cell_density;

  auto* rm = simulation.GetResourceManager();
  auto* cell = new Moving_cell({0.0, 0.0, 0.0});
  cell->SetDiameter(10.);
  cell->SetMass(cell_mass);

  rm->AddAgent(cell);

  const int time_steps = 100;

  // Track positions

  std::vector<Real3> cell_positions;
  auto* track_pos_op = NewOperation("track_position");
  track_pos_op->GetImplementation<TrackPosition>()->positions_ =
      &cell_positions;
  track_pos_op->frequency_ = 1;  // 0.1 min
  scheduler->ScheduleOp(track_pos_op);

  // Apply force
  auto* apply_force = NewOperation("apply_force");
  apply_force->GetImplementation<ApplyForce>()->initial_speed_ = {10.0, 0.0, 0.0};
  scheduler->ScheduleOp(apply_force);
  apply_force->frequency_ = time_steps;  // 0.1 min

  // Simulate dissipative force (e.g. friction from extracellular matrix)
  auto* friction = NewOperation("dissipative_force");
  // F_loc = m*Dv/Dt = m*(1um/Dt * 1/Dt) = m Newton (for Dt = 1)
  // friction coeff = 0.1 F_loc

  double friction_coefficient = 0.1;
  friction->GetImplementation<DissipativeForce>()->friction_coefficient_ =
      friction_coefficient;
  friction->frequency_ = 1;  // 0.1 min
  scheduler->ScheduleOp(friction);

  // Run simulation for 10 minutes (100 steps, 1 step = 0.1 min )
  scheduler->Simulate(time_steps);

  std::cout << "Simulation completed successfully!" << std::endl;

  std::ofstream file;
  if (!file.is_open()) {
    file.open("positions.csv");
  }

  for (size_t i = 0; i < cell_positions.size(); i++) {
    file << i << "\t " << cell_positions[i] << std::endl;
  }

  file.close();

  return 0;
}

}  // namespace bdm

#endif  // UNIT_TEST_MECHANICS_H_

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"", payloadCode, "@",
"bdm::AgentPointer<bdm::Agent>", payloadCode, "@",
"bdm::ApplyForce", payloadCode, "@",
"bdm::DissipativeForce", payloadCode, "@",
"bdm::Environment", payloadCode, "@",
"bdm::InPlaceExecutionContext", payloadCode, "@",
"bdm::Moving_cell", payloadCode, "@",
"bdm::Param::BoundSpaceMode", payloadCode, "@",
"bdm::Param::ExecutionOrder", payloadCode, "@",
"bdm::Param::MappedDataArrayMode", payloadCode, "@",
"bdm::Param::NumericalODESolver", payloadCode, "@",
"bdm::Param::ThreadSafetyMechanism", payloadCode, "@",
"bdm::ProgressBar", payloadCode, "@",
"bdm::SharedData<ULong64_t>", payloadCode, "@",
"bdm::SharedData<bdm::MathArray<double,3> >", payloadCode, "@",
"bdm::SharedData<bdm::MathArray<double,4> >", payloadCode, "@",
"bdm::SharedData<double>", payloadCode, "@",
"bdm::SharedData<float>", payloadCode, "@",
"bdm::SharedData<vector<bdm::AgentUid> >", payloadCode, "@",
"bdm::TrackPosition", payloadCode, "@",
"bdm::UnorderedFlatmap<TClass*,vector<bdm::Agent*> >", payloadCode, "@",
"bdm::VectorField", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("libunit-test-mechanics_dict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_libunitmItestmImechanics_dict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_libunitmItestmImechanics_dict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_libunitmItestmImechanics_dict() {
  TriggerDictionaryInitialization_libunitmItestmImechanics_dict_Impl();
}
