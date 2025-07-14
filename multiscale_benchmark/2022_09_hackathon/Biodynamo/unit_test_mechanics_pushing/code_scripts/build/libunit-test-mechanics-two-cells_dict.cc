// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIUsersdIhp024dIobservatory_benchmarkdImultiscale_benchmarkdI2022_09_hackathondIBiodynamodIunit_test_mechanics_pushingdIcode_scriptsdIbuilddIlibunitmItestmImechanicsmItwomIcells_dict
#define R__NO_DEPRECATION

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "ROOT/RConfig.hxx"
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
#include "/Users/hp024/observatory_benchmark/multiscale_benchmark/2022_09_hackathon/Biodynamo/unit_test_mechanics_pushing/code_scripts/src/behaviours.h"
#include "/Users/hp024/observatory_benchmark/multiscale_benchmark/2022_09_hackathon/Biodynamo/unit_test_mechanics_pushing/code_scripts/src/cell_cell_force.h"
#include "/Users/hp024/observatory_benchmark/multiscale_benchmark/2022_09_hackathon/Biodynamo/unit_test_mechanics_pushing/code_scripts/src/custom_ops.h"
#include "/Users/hp024/observatory_benchmark/multiscale_benchmark/2022_09_hackathon/Biodynamo/unit_test_mechanics_pushing/code_scripts/src/moving_cell.h"
#include "/Users/hp024/observatory_benchmark/multiscale_benchmark/2022_09_hackathon/Biodynamo/unit_test_mechanics_pushing/code_scripts/src/sim_param.h"
#include "/Users/hp024/observatory_benchmark/multiscale_benchmark/2022_09_hackathon/Biodynamo/unit_test_mechanics_pushing/code_scripts/src/unit-test-mechanics-two-cells.h"

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
   static TClass *bdmcLcLFunctorlEvoidcObdmcLcLIteratorlEULong64_tgRmUgR_Dictionary();
   static void bdmcLcLFunctorlEvoidcObdmcLcLIteratorlEULong64_tgRmUgR_TClassManip(TClass*);
   static void delete_bdmcLcLFunctorlEvoidcObdmcLcLIteratorlEULong64_tgRmUgR(void *p);
   static void deleteArray_bdmcLcLFunctorlEvoidcObdmcLcLIteratorlEULong64_tgRmUgR(void *p);
   static void destruct_bdmcLcLFunctorlEvoidcObdmcLcLIteratorlEULong64_tgRmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::bdm::Functor<void,bdm::Iterator<ULong64_t>*>*)
   {
      ::bdm::Functor<void,bdm::Iterator<ULong64_t>*> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::bdm::Functor<void,bdm::Iterator<ULong64_t>*>));
      static ::ROOT::TGenericClassInfo 
         instance("bdm::Functor<void,bdm::Iterator<ULong64_t>*>", "core/functor.h", 24,
                  typeid(::bdm::Functor<void,bdm::Iterator<ULong64_t>*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &bdmcLcLFunctorlEvoidcObdmcLcLIteratorlEULong64_tgRmUgR_Dictionary, isa_proxy, 4,
                  sizeof(::bdm::Functor<void,bdm::Iterator<ULong64_t>*>) );
      instance.SetDelete(&delete_bdmcLcLFunctorlEvoidcObdmcLcLIteratorlEULong64_tgRmUgR);
      instance.SetDeleteArray(&deleteArray_bdmcLcLFunctorlEvoidcObdmcLcLIteratorlEULong64_tgRmUgR);
      instance.SetDestructor(&destruct_bdmcLcLFunctorlEvoidcObdmcLcLIteratorlEULong64_tgRmUgR);

      instance.AdoptAlternate(::ROOT::AddClassAlternate("bdm::Functor<void,bdm::Iterator<ULong64_t>*>","bdm::Functor<void, bdm::Iterator<unsigned long long>*>"));
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::bdm::Functor<void,bdm::Iterator<ULong64_t>*>*)
   {
      return GenerateInitInstanceLocal(static_cast<::bdm::Functor<void,bdm::Iterator<ULong64_t>*>*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::bdm::Functor<void,bdm::Iterator<ULong64_t>*>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *bdmcLcLFunctorlEvoidcObdmcLcLIteratorlEULong64_tgRmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const ::bdm::Functor<void,bdm::Iterator<ULong64_t>*>*>(nullptr))->GetClass();
      bdmcLcLFunctorlEvoidcObdmcLcLIteratorlEULong64_tgRmUgR_TClassManip(theClass);
   return theClass;
   }

   static void bdmcLcLFunctorlEvoidcObdmcLcLIteratorlEULong64_tgRmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *bdmcLcLFixedSizeVectorlEconstsPbdmcLcLUniformGridEnvironmentcLcLBoxmUcO27gR_Dictionary();
   static void bdmcLcLFixedSizeVectorlEconstsPbdmcLcLUniformGridEnvironmentcLcLBoxmUcO27gR_TClassManip(TClass*);
   static void *new_bdmcLcLFixedSizeVectorlEconstsPbdmcLcLUniformGridEnvironmentcLcLBoxmUcO27gR(void *p = nullptr);
   static void *newArray_bdmcLcLFixedSizeVectorlEconstsPbdmcLcLUniformGridEnvironmentcLcLBoxmUcO27gR(Long_t size, void *p);
   static void delete_bdmcLcLFixedSizeVectorlEconstsPbdmcLcLUniformGridEnvironmentcLcLBoxmUcO27gR(void *p);
   static void deleteArray_bdmcLcLFixedSizeVectorlEconstsPbdmcLcLUniformGridEnvironmentcLcLBoxmUcO27gR(void *p);
   static void destruct_bdmcLcLFixedSizeVectorlEconstsPbdmcLcLUniformGridEnvironmentcLcLBoxmUcO27gR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::bdm::FixedSizeVector<const bdm::UniformGridEnvironment::Box*,27>*)
   {
      ::bdm::FixedSizeVector<const bdm::UniformGridEnvironment::Box*,27> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::bdm::FixedSizeVector<const bdm::UniformGridEnvironment::Box*,27>));
      static ::ROOT::TGenericClassInfo 
         instance("bdm::FixedSizeVector<const bdm::UniformGridEnvironment::Box*,27>", "core/container/fixed_size_vector.h", 30,
                  typeid(::bdm::FixedSizeVector<const bdm::UniformGridEnvironment::Box*,27>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &bdmcLcLFixedSizeVectorlEconstsPbdmcLcLUniformGridEnvironmentcLcLBoxmUcO27gR_Dictionary, isa_proxy, 4,
                  sizeof(::bdm::FixedSizeVector<const bdm::UniformGridEnvironment::Box*,27>) );
      instance.SetNew(&new_bdmcLcLFixedSizeVectorlEconstsPbdmcLcLUniformGridEnvironmentcLcLBoxmUcO27gR);
      instance.SetNewArray(&newArray_bdmcLcLFixedSizeVectorlEconstsPbdmcLcLUniformGridEnvironmentcLcLBoxmUcO27gR);
      instance.SetDelete(&delete_bdmcLcLFixedSizeVectorlEconstsPbdmcLcLUniformGridEnvironmentcLcLBoxmUcO27gR);
      instance.SetDeleteArray(&deleteArray_bdmcLcLFixedSizeVectorlEconstsPbdmcLcLUniformGridEnvironmentcLcLBoxmUcO27gR);
      instance.SetDestructor(&destruct_bdmcLcLFixedSizeVectorlEconstsPbdmcLcLUniformGridEnvironmentcLcLBoxmUcO27gR);

      instance.AdoptAlternate(::ROOT::AddClassAlternate("bdm::FixedSizeVector<const bdm::UniformGridEnvironment::Box*,27>","bdm::FixedSizeVector<bdm::UniformGridEnvironment::Box const*, 27ul>"));
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::bdm::FixedSizeVector<const bdm::UniformGridEnvironment::Box*,27>*)
   {
      return GenerateInitInstanceLocal(static_cast<::bdm::FixedSizeVector<const bdm::UniformGridEnvironment::Box*,27>*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::bdm::FixedSizeVector<const bdm::UniformGridEnvironment::Box*,27>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *bdmcLcLFixedSizeVectorlEconstsPbdmcLcLUniformGridEnvironmentcLcLBoxmUcO27gR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const ::bdm::FixedSizeVector<const bdm::UniformGridEnvironment::Box*,27>*>(nullptr))->GetClass();
      bdmcLcLFixedSizeVectorlEconstsPbdmcLcLUniformGridEnvironmentcLcLBoxmUcO27gR_TClassManip(theClass);
   return theClass;
   }

   static void bdmcLcLFixedSizeVectorlEconstsPbdmcLcLUniformGridEnvironmentcLcLBoxmUcO27gR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *bdmcLcLFixedSizeVectorlEULong64_tcO27gR_Dictionary();
   static void bdmcLcLFixedSizeVectorlEULong64_tcO27gR_TClassManip(TClass*);
   static void *new_bdmcLcLFixedSizeVectorlEULong64_tcO27gR(void *p = nullptr);
   static void *newArray_bdmcLcLFixedSizeVectorlEULong64_tcO27gR(Long_t size, void *p);
   static void delete_bdmcLcLFixedSizeVectorlEULong64_tcO27gR(void *p);
   static void deleteArray_bdmcLcLFixedSizeVectorlEULong64_tcO27gR(void *p);
   static void destruct_bdmcLcLFixedSizeVectorlEULong64_tcO27gR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::bdm::FixedSizeVector<ULong64_t,27>*)
   {
      ::bdm::FixedSizeVector<ULong64_t,27> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::bdm::FixedSizeVector<ULong64_t,27>));
      static ::ROOT::TGenericClassInfo 
         instance("bdm::FixedSizeVector<ULong64_t,27>", "core/container/fixed_size_vector.h", 30,
                  typeid(::bdm::FixedSizeVector<ULong64_t,27>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &bdmcLcLFixedSizeVectorlEULong64_tcO27gR_Dictionary, isa_proxy, 4,
                  sizeof(::bdm::FixedSizeVector<ULong64_t,27>) );
      instance.SetNew(&new_bdmcLcLFixedSizeVectorlEULong64_tcO27gR);
      instance.SetNewArray(&newArray_bdmcLcLFixedSizeVectorlEULong64_tcO27gR);
      instance.SetDelete(&delete_bdmcLcLFixedSizeVectorlEULong64_tcO27gR);
      instance.SetDeleteArray(&deleteArray_bdmcLcLFixedSizeVectorlEULong64_tcO27gR);
      instance.SetDestructor(&destruct_bdmcLcLFixedSizeVectorlEULong64_tcO27gR);

      instance.AdoptAlternate(::ROOT::AddClassAlternate("bdm::FixedSizeVector<ULong64_t,27>","bdm::FixedSizeVector<unsigned long long, 27ul>"));
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::bdm::FixedSizeVector<ULong64_t,27>*)
   {
      return GenerateInitInstanceLocal(static_cast<::bdm::FixedSizeVector<ULong64_t,27>*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::bdm::FixedSizeVector<ULong64_t,27>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *bdmcLcLFixedSizeVectorlEULong64_tcO27gR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const ::bdm::FixedSizeVector<ULong64_t,27>*>(nullptr))->GetClass();
      bdmcLcLFixedSizeVectorlEULong64_tcO27gR_TClassManip(theClass);
   return theClass;
   }

   static void bdmcLcLFixedSizeVectorlEULong64_tcO27gR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *bdmcLcLFixedSizeVectorlEunsignedsPlongcO14gR_Dictionary();
   static void bdmcLcLFixedSizeVectorlEunsignedsPlongcO14gR_TClassManip(TClass*);
   static void *new_bdmcLcLFixedSizeVectorlEunsignedsPlongcO14gR(void *p = nullptr);
   static void *newArray_bdmcLcLFixedSizeVectorlEunsignedsPlongcO14gR(Long_t size, void *p);
   static void delete_bdmcLcLFixedSizeVectorlEunsignedsPlongcO14gR(void *p);
   static void deleteArray_bdmcLcLFixedSizeVectorlEunsignedsPlongcO14gR(void *p);
   static void destruct_bdmcLcLFixedSizeVectorlEunsignedsPlongcO14gR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::bdm::FixedSizeVector<unsigned long,14>*)
   {
      ::bdm::FixedSizeVector<unsigned long,14> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::bdm::FixedSizeVector<unsigned long,14>));
      static ::ROOT::TGenericClassInfo 
         instance("bdm::FixedSizeVector<unsigned long,14>", "core/container/fixed_size_vector.h", 30,
                  typeid(::bdm::FixedSizeVector<unsigned long,14>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &bdmcLcLFixedSizeVectorlEunsignedsPlongcO14gR_Dictionary, isa_proxy, 4,
                  sizeof(::bdm::FixedSizeVector<unsigned long,14>) );
      instance.SetNew(&new_bdmcLcLFixedSizeVectorlEunsignedsPlongcO14gR);
      instance.SetNewArray(&newArray_bdmcLcLFixedSizeVectorlEunsignedsPlongcO14gR);
      instance.SetDelete(&delete_bdmcLcLFixedSizeVectorlEunsignedsPlongcO14gR);
      instance.SetDeleteArray(&deleteArray_bdmcLcLFixedSizeVectorlEunsignedsPlongcO14gR);
      instance.SetDestructor(&destruct_bdmcLcLFixedSizeVectorlEunsignedsPlongcO14gR);

      instance.AdoptAlternate(::ROOT::AddClassAlternate("bdm::FixedSizeVector<unsigned long,14>","bdm::FixedSizeVector<unsigned long, 14ul>"));
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::bdm::FixedSizeVector<unsigned long,14>*)
   {
      return GenerateInitInstanceLocal(static_cast<::bdm::FixedSizeVector<unsigned long,14>*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::bdm::FixedSizeVector<unsigned long,14>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *bdmcLcLFixedSizeVectorlEunsignedsPlongcO14gR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const ::bdm::FixedSizeVector<unsigned long,14>*>(nullptr))->GetClass();
      bdmcLcLFixedSizeVectorlEunsignedsPlongcO14gR_TClassManip(theClass);
   return theClass;
   }

   static void bdmcLcLFixedSizeVectorlEunsignedsPlongcO14gR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

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
      return GenerateInitInstanceLocal(static_cast<::bdm::AgentPointer<bdm::Agent>*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::bdm::AgentPointer<bdm::Agent>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *bdmcLcLAgentPointerlEbdmcLcLAgentgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const ::bdm::AgentPointer<bdm::Agent>*>(nullptr))->GetClass();
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
         instance("bdm::SharedData<ULong64_t>::Iterator", "core/container/shared_data.h", 78,
                  typeid(::bdm::SharedData<ULong64_t>::Iterator), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &bdmcLcLSharedDatalEULong64_tgRcLcLIterator_Dictionary, isa_proxy, 4,
                  sizeof(::bdm::SharedData<ULong64_t>::Iterator) );
      instance.SetNew(&new_bdmcLcLSharedDatalEULong64_tgRcLcLIterator);
      instance.SetNewArray(&newArray_bdmcLcLSharedDatalEULong64_tgRcLcLIterator);
      instance.SetDelete(&delete_bdmcLcLSharedDatalEULong64_tgRcLcLIterator);
      instance.SetDeleteArray(&deleteArray_bdmcLcLSharedDatalEULong64_tgRcLcLIterator);
      instance.SetDestructor(&destruct_bdmcLcLSharedDatalEULong64_tgRcLcLIterator);

      instance.AdoptAlternate(::ROOT::AddClassAlternate("bdm::SharedData<ULong64_t>::Iterator","bdm::SharedData<unsigned long long>::Iterator"));
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::bdm::SharedData<ULong64_t>::Iterator*)
   {
      return GenerateInitInstanceLocal(static_cast<::bdm::SharedData<ULong64_t>::Iterator*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::bdm::SharedData<ULong64_t>::Iterator*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *bdmcLcLSharedDatalEULong64_tgRcLcLIterator_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const ::bdm::SharedData<ULong64_t>::Iterator*>(nullptr))->GetClass();
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
         instance("bdm::SharedData<double>", ::bdm::SharedData<double>::Class_Version(), "core/container/shared_data.h", 48,
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
      return GenerateInitInstanceLocal(static_cast<::bdm::SharedData<double>*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::bdm::SharedData<double>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *bdmcLcLSharedDatalEdoublegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const ::bdm::SharedData<double>*>(nullptr))->GetClass();
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
         instance("bdm::SharedData<float>", ::bdm::SharedData<float>::Class_Version(), "core/container/shared_data.h", 48,
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
      return GenerateInitInstanceLocal(static_cast<::bdm::SharedData<float>*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::bdm::SharedData<float>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *bdmcLcLSharedDatalEfloatgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const ::bdm::SharedData<float>*>(nullptr))->GetClass();
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
      return GenerateInitInstanceLocal(static_cast<::bdm::ProgressBar*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::bdm::ProgressBar*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *bdmcLcLProgressBar_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const ::bdm::ProgressBar*>(nullptr))->GetClass();
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
      return GenerateInitInstanceLocal(static_cast<::bdm::VectorField*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::bdm::VectorField*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static TClass *bdmcLcLUniformGridEnvironmentcLcLBox_Dictionary();
   static void bdmcLcLUniformGridEnvironmentcLcLBox_TClassManip(TClass*);
   static void *new_bdmcLcLUniformGridEnvironmentcLcLBox(void *p = nullptr);
   static void *newArray_bdmcLcLUniformGridEnvironmentcLcLBox(Long_t size, void *p);
   static void delete_bdmcLcLUniformGridEnvironmentcLcLBox(void *p);
   static void deleteArray_bdmcLcLUniformGridEnvironmentcLcLBox(void *p);
   static void destruct_bdmcLcLUniformGridEnvironmentcLcLBox(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::bdm::UniformGridEnvironment::Box*)
   {
      ::bdm::UniformGridEnvironment::Box *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::bdm::UniformGridEnvironment::Box));
      static ::ROOT::TGenericClassInfo 
         instance("bdm::UniformGridEnvironment::Box", "core/environment/uniform_grid_environment.h", 69,
                  typeid(::bdm::UniformGridEnvironment::Box), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &bdmcLcLUniformGridEnvironmentcLcLBox_Dictionary, isa_proxy, 4,
                  sizeof(::bdm::UniformGridEnvironment::Box) );
      instance.SetNew(&new_bdmcLcLUniformGridEnvironmentcLcLBox);
      instance.SetNewArray(&newArray_bdmcLcLUniformGridEnvironmentcLcLBox);
      instance.SetDelete(&delete_bdmcLcLUniformGridEnvironmentcLcLBox);
      instance.SetDeleteArray(&deleteArray_bdmcLcLUniformGridEnvironmentcLcLBox);
      instance.SetDestructor(&destruct_bdmcLcLUniformGridEnvironmentcLcLBox);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::bdm::UniformGridEnvironment::Box*)
   {
      return GenerateInitInstanceLocal(static_cast<::bdm::UniformGridEnvironment::Box*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::bdm::UniformGridEnvironment::Box*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *bdmcLcLUniformGridEnvironmentcLcLBox_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const ::bdm::UniformGridEnvironment::Box*>(nullptr))->GetClass();
      bdmcLcLUniformGridEnvironmentcLcLBox_TClassManip(theClass);
   return theClass;
   }

   static void bdmcLcLUniformGridEnvironmentcLcLBox_TClassManip(TClass* ){
   }

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
      return GenerateInitInstanceLocal(static_cast<::bdm::Moving_cell*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::bdm::Moving_cell*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_bdmcLcLMove(void *p = nullptr);
   static void *newArray_bdmcLcLMove(Long_t size, void *p);
   static void delete_bdmcLcLMove(void *p);
   static void deleteArray_bdmcLcLMove(void *p);
   static void destruct_bdmcLcLMove(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::bdm::Move*)
   {
      ::bdm::Move *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::bdm::Move >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("bdm::Move", ::bdm::Move::Class_Version(), "", 21,
                  typeid(::bdm::Move), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::bdm::Move::Dictionary, isa_proxy, 4,
                  sizeof(::bdm::Move) );
      instance.SetNew(&new_bdmcLcLMove);
      instance.SetNewArray(&newArray_bdmcLcLMove);
      instance.SetDelete(&delete_bdmcLcLMove);
      instance.SetDeleteArray(&deleteArray_bdmcLcLMove);
      instance.SetDestructor(&destruct_bdmcLcLMove);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::bdm::Move*)
   {
      return GenerateInitInstanceLocal(static_cast<::bdm::Move*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::bdm::Move*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static TClass *bdmcLcLCellCellForce_Dictionary();
   static void bdmcLcLCellCellForce_TClassManip(TClass*);
   static void *new_bdmcLcLCellCellForce(void *p = nullptr);
   static void *newArray_bdmcLcLCellCellForce(Long_t size, void *p);
   static void delete_bdmcLcLCellCellForce(void *p);
   static void deleteArray_bdmcLcLCellCellForce(void *p);
   static void destruct_bdmcLcLCellCellForce(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::bdm::CellCellForce*)
   {
      ::bdm::CellCellForce *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::bdm::CellCellForce));
      static ::ROOT::TGenericClassInfo 
         instance("bdm::CellCellForce", "", 66,
                  typeid(::bdm::CellCellForce), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &bdmcLcLCellCellForce_Dictionary, isa_proxy, 4,
                  sizeof(::bdm::CellCellForce) );
      instance.SetNew(&new_bdmcLcLCellCellForce);
      instance.SetNewArray(&newArray_bdmcLcLCellCellForce);
      instance.SetDelete(&delete_bdmcLcLCellCellForce);
      instance.SetDeleteArray(&deleteArray_bdmcLcLCellCellForce);
      instance.SetDestructor(&destruct_bdmcLcLCellCellForce);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::bdm::CellCellForce*)
   {
      return GenerateInitInstanceLocal(static_cast<::bdm::CellCellForce*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::bdm::CellCellForce*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *bdmcLcLCellCellForce_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const ::bdm::CellCellForce*>(nullptr))->GetClass();
      bdmcLcLCellCellForce_TClassManip(theClass);
   return theClass;
   }

   static void bdmcLcLCellCellForce_TClassManip(TClass* ){
   }

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
         instance("bdm::DissipativeForce", "", 86,
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
      return GenerateInitInstanceLocal(static_cast<::bdm::DissipativeForce*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::bdm::DissipativeForce*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *bdmcLcLDissipativeForce_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const ::bdm::DissipativeForce*>(nullptr))->GetClass();
      bdmcLcLDissipativeForce_TClassManip(theClass);
   return theClass;
   }

   static void bdmcLcLDissipativeForce_TClassManip(TClass* ){
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
         instance("bdm::TrackPosition", "", 100,
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
      return GenerateInitInstanceLocal(static_cast<::bdm::TrackPosition*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::bdm::TrackPosition*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *bdmcLcLTrackPosition_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const ::bdm::TrackPosition*>(nullptr))->GetClass();
      bdmcLcLTrackPosition_TClassManip(theClass);
   return theClass;
   }

   static void bdmcLcLTrackPosition_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static void *new_bdmcLcLSimParam(void *p = nullptr);
   static void *newArray_bdmcLcLSimParam(Long_t size, void *p);
   static void delete_bdmcLcLSimParam(void *p);
   static void deleteArray_bdmcLcLSimParam(void *p);
   static void destruct_bdmcLcLSimParam(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::bdm::SimParam*)
   {
      ::bdm::SimParam *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::bdm::SimParam >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("bdm::SimParam", ::bdm::SimParam::Class_Version(), "", 175,
                  typeid(::bdm::SimParam), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::bdm::SimParam::Dictionary, isa_proxy, 4,
                  sizeof(::bdm::SimParam) );
      instance.SetNew(&new_bdmcLcLSimParam);
      instance.SetNewArray(&newArray_bdmcLcLSimParam);
      instance.SetDelete(&delete_bdmcLcLSimParam);
      instance.SetDeleteArray(&deleteArray_bdmcLcLSimParam);
      instance.SetDestructor(&destruct_bdmcLcLSimParam);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::bdm::SimParam*)
   {
      return GenerateInitInstanceLocal(static_cast<::bdm::SimParam*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::bdm::SimParam*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static TClass *bdmcLcLAgentVectorlEbdmcLcLAgentHandlegR_Dictionary();
   static void bdmcLcLAgentVectorlEbdmcLcLAgentHandlegR_TClassManip(TClass*);
   static void *new_bdmcLcLAgentVectorlEbdmcLcLAgentHandlegR(void *p = nullptr);
   static void *newArray_bdmcLcLAgentVectorlEbdmcLcLAgentHandlegR(Long_t size, void *p);
   static void delete_bdmcLcLAgentVectorlEbdmcLcLAgentHandlegR(void *p);
   static void deleteArray_bdmcLcLAgentVectorlEbdmcLcLAgentHandlegR(void *p);
   static void destruct_bdmcLcLAgentVectorlEbdmcLcLAgentHandlegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::bdm::AgentVector<bdm::AgentHandle>*)
   {
      ::bdm::AgentVector<bdm::AgentHandle> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::bdm::AgentVector<bdm::AgentHandle>));
      static ::ROOT::TGenericClassInfo 
         instance("bdm::AgentVector<bdm::AgentHandle>", "core/container/agent_vector.h", 31,
                  typeid(::bdm::AgentVector<bdm::AgentHandle>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &bdmcLcLAgentVectorlEbdmcLcLAgentHandlegR_Dictionary, isa_proxy, 4,
                  sizeof(::bdm::AgentVector<bdm::AgentHandle>) );
      instance.SetNew(&new_bdmcLcLAgentVectorlEbdmcLcLAgentHandlegR);
      instance.SetNewArray(&newArray_bdmcLcLAgentVectorlEbdmcLcLAgentHandlegR);
      instance.SetDelete(&delete_bdmcLcLAgentVectorlEbdmcLcLAgentHandlegR);
      instance.SetDeleteArray(&deleteArray_bdmcLcLAgentVectorlEbdmcLcLAgentHandlegR);
      instance.SetDestructor(&destruct_bdmcLcLAgentVectorlEbdmcLcLAgentHandlegR);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::bdm::AgentVector<bdm::AgentHandle>*)
   {
      return GenerateInitInstanceLocal(static_cast<::bdm::AgentVector<bdm::AgentHandle>*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::bdm::AgentVector<bdm::AgentHandle>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *bdmcLcLAgentVectorlEbdmcLcLAgentHandlegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const ::bdm::AgentVector<bdm::AgentHandle>*>(nullptr))->GetClass();
      bdmcLcLAgentVectorlEbdmcLcLAgentHandlegR_TClassManip(theClass);
   return theClass;
   }

   static void bdmcLcLAgentVectorlEbdmcLcLAgentHandlegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *bdmcLcLMortonOrder_Dictionary();
   static void bdmcLcLMortonOrder_TClassManip(TClass*);
   static void *new_bdmcLcLMortonOrder(void *p = nullptr);
   static void *newArray_bdmcLcLMortonOrder(Long_t size, void *p);
   static void delete_bdmcLcLMortonOrder(void *p);
   static void deleteArray_bdmcLcLMortonOrder(void *p);
   static void destruct_bdmcLcLMortonOrder(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::bdm::MortonOrder*)
   {
      ::bdm::MortonOrder *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::bdm::MortonOrder));
      static ::ROOT::TGenericClassInfo 
         instance("bdm::MortonOrder", "core/environment/morton_order.h", 27,
                  typeid(::bdm::MortonOrder), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &bdmcLcLMortonOrder_Dictionary, isa_proxy, 4,
                  sizeof(::bdm::MortonOrder) );
      instance.SetNew(&new_bdmcLcLMortonOrder);
      instance.SetNewArray(&newArray_bdmcLcLMortonOrder);
      instance.SetDelete(&delete_bdmcLcLMortonOrder);
      instance.SetDeleteArray(&deleteArray_bdmcLcLMortonOrder);
      instance.SetDestructor(&destruct_bdmcLcLMortonOrder);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::bdm::MortonOrder*)
   {
      return GenerateInitInstanceLocal(static_cast<::bdm::MortonOrder*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::bdm::MortonOrder*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *bdmcLcLMortonOrder_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const ::bdm::MortonOrder*>(nullptr))->GetClass();
      bdmcLcLMortonOrder_TClassManip(theClass);
   return theClass;
   }

   static void bdmcLcLMortonOrder_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *bdmcLcLUniformGridEnvironmentcLcLBoxcLcLIterator_Dictionary();
   static void bdmcLcLUniformGridEnvironmentcLcLBoxcLcLIterator_TClassManip(TClass*);
   static void delete_bdmcLcLUniformGridEnvironmentcLcLBoxcLcLIterator(void *p);
   static void deleteArray_bdmcLcLUniformGridEnvironmentcLcLBoxcLcLIterator(void *p);
   static void destruct_bdmcLcLUniformGridEnvironmentcLcLBoxcLcLIterator(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::bdm::UniformGridEnvironment::Box::Iterator*)
   {
      ::bdm::UniformGridEnvironment::Box::Iterator *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::bdm::UniformGridEnvironment::Box::Iterator));
      static ::ROOT::TGenericClassInfo 
         instance("bdm::UniformGridEnvironment::Box::Iterator", "core/environment/uniform_grid_environment.h", 129,
                  typeid(::bdm::UniformGridEnvironment::Box::Iterator), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &bdmcLcLUniformGridEnvironmentcLcLBoxcLcLIterator_Dictionary, isa_proxy, 4,
                  sizeof(::bdm::UniformGridEnvironment::Box::Iterator) );
      instance.SetDelete(&delete_bdmcLcLUniformGridEnvironmentcLcLBoxcLcLIterator);
      instance.SetDeleteArray(&deleteArray_bdmcLcLUniformGridEnvironmentcLcLBoxcLcLIterator);
      instance.SetDestructor(&destruct_bdmcLcLUniformGridEnvironmentcLcLBoxcLcLIterator);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::bdm::UniformGridEnvironment::Box::Iterator*)
   {
      return GenerateInitInstanceLocal(static_cast<::bdm::UniformGridEnvironment::Box::Iterator*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::bdm::UniformGridEnvironment::Box::Iterator*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *bdmcLcLUniformGridEnvironmentcLcLBoxcLcLIterator_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const ::bdm::UniformGridEnvironment::Box::Iterator*>(nullptr))->GetClass();
      bdmcLcLUniformGridEnvironmentcLcLBoxcLcLIterator_TClassManip(theClass);
   return theClass;
   }

   static void bdmcLcLUniformGridEnvironmentcLcLBoxcLcLIterator_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *bdmcLcLUniformGridEnvironmentcLcLNeighborIterator_Dictionary();
   static void bdmcLcLUniformGridEnvironmentcLcLNeighborIterator_TClassManip(TClass*);
   static void delete_bdmcLcLUniformGridEnvironmentcLcLNeighborIterator(void *p);
   static void deleteArray_bdmcLcLUniformGridEnvironmentcLcLNeighborIterator(void *p);
   static void destruct_bdmcLcLUniformGridEnvironmentcLcLNeighborIterator(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::bdm::UniformGridEnvironment::NeighborIterator*)
   {
      ::bdm::UniformGridEnvironment::NeighborIterator *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::bdm::UniformGridEnvironment::NeighborIterator));
      static ::ROOT::TGenericClassInfo 
         instance("bdm::UniformGridEnvironment::NeighborIterator", "core/environment/uniform_grid_environment.h", 163,
                  typeid(::bdm::UniformGridEnvironment::NeighborIterator), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &bdmcLcLUniformGridEnvironmentcLcLNeighborIterator_Dictionary, isa_proxy, 4,
                  sizeof(::bdm::UniformGridEnvironment::NeighborIterator) );
      instance.SetDelete(&delete_bdmcLcLUniformGridEnvironmentcLcLNeighborIterator);
      instance.SetDeleteArray(&deleteArray_bdmcLcLUniformGridEnvironmentcLcLNeighborIterator);
      instance.SetDestructor(&destruct_bdmcLcLUniformGridEnvironmentcLcLNeighborIterator);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::bdm::UniformGridEnvironment::NeighborIterator*)
   {
      return GenerateInitInstanceLocal(static_cast<::bdm::UniformGridEnvironment::NeighborIterator*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::bdm::UniformGridEnvironment::NeighborIterator*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *bdmcLcLUniformGridEnvironmentcLcLNeighborIterator_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const ::bdm::UniformGridEnvironment::NeighborIterator*>(nullptr))->GetClass();
      bdmcLcLUniformGridEnvironmentcLcLNeighborIterator_TClassManip(theClass);
   return theClass;
   }

   static void bdmcLcLUniformGridEnvironmentcLcLNeighborIterator_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *bdmcLcLUniformGridEnvironmentcLcLAssignToBoxesFunctor_Dictionary();
   static void bdmcLcLUniformGridEnvironmentcLcLAssignToBoxesFunctor_TClassManip(TClass*);
   static void delete_bdmcLcLUniformGridEnvironmentcLcLAssignToBoxesFunctor(void *p);
   static void deleteArray_bdmcLcLUniformGridEnvironmentcLcLAssignToBoxesFunctor(void *p);
   static void destruct_bdmcLcLUniformGridEnvironmentcLcLAssignToBoxesFunctor(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::bdm::UniformGridEnvironment::AssignToBoxesFunctor*)
   {
      ::bdm::UniformGridEnvironment::AssignToBoxesFunctor *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::bdm::UniformGridEnvironment::AssignToBoxesFunctor));
      static ::ROOT::TGenericClassInfo 
         instance("bdm::UniformGridEnvironment::AssignToBoxesFunctor", "core/environment/uniform_grid_environment.h", 257,
                  typeid(::bdm::UniformGridEnvironment::AssignToBoxesFunctor), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &bdmcLcLUniformGridEnvironmentcLcLAssignToBoxesFunctor_Dictionary, isa_proxy, 4,
                  sizeof(::bdm::UniformGridEnvironment::AssignToBoxesFunctor) );
      instance.SetDelete(&delete_bdmcLcLUniformGridEnvironmentcLcLAssignToBoxesFunctor);
      instance.SetDeleteArray(&deleteArray_bdmcLcLUniformGridEnvironmentcLcLAssignToBoxesFunctor);
      instance.SetDestructor(&destruct_bdmcLcLUniformGridEnvironmentcLcLAssignToBoxesFunctor);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::bdm::UniformGridEnvironment::AssignToBoxesFunctor*)
   {
      return GenerateInitInstanceLocal(static_cast<::bdm::UniformGridEnvironment::AssignToBoxesFunctor*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::bdm::UniformGridEnvironment::AssignToBoxesFunctor*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *bdmcLcLUniformGridEnvironmentcLcLAssignToBoxesFunctor_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const ::bdm::UniformGridEnvironment::AssignToBoxesFunctor*>(nullptr))->GetClass();
      bdmcLcLUniformGridEnvironmentcLcLAssignToBoxesFunctor_TClassManip(theClass);
   return theClass;
   }

   static void bdmcLcLUniformGridEnvironmentcLcLAssignToBoxesFunctor_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *bdmcLcLUniformGridEnvironmentcLcLGridNeighborMutexBuilder_Dictionary();
   static void bdmcLcLUniformGridEnvironmentcLcLGridNeighborMutexBuilder_TClassManip(TClass*);
   static void *new_bdmcLcLUniformGridEnvironmentcLcLGridNeighborMutexBuilder(void *p = nullptr);
   static void *newArray_bdmcLcLUniformGridEnvironmentcLcLGridNeighborMutexBuilder(Long_t size, void *p);
   static void delete_bdmcLcLUniformGridEnvironmentcLcLGridNeighborMutexBuilder(void *p);
   static void deleteArray_bdmcLcLUniformGridEnvironmentcLcLGridNeighborMutexBuilder(void *p);
   static void destruct_bdmcLcLUniformGridEnvironmentcLcLGridNeighborMutexBuilder(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::bdm::UniformGridEnvironment::GridNeighborMutexBuilder*)
   {
      ::bdm::UniformGridEnvironment::GridNeighborMutexBuilder *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::bdm::UniformGridEnvironment::GridNeighborMutexBuilder));
      static ::ROOT::TGenericClassInfo 
         instance("bdm::UniformGridEnvironment::GridNeighborMutexBuilder", "core/environment/uniform_grid_environment.h", 540,
                  typeid(::bdm::UniformGridEnvironment::GridNeighborMutexBuilder), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &bdmcLcLUniformGridEnvironmentcLcLGridNeighborMutexBuilder_Dictionary, isa_proxy, 4,
                  sizeof(::bdm::UniformGridEnvironment::GridNeighborMutexBuilder) );
      instance.SetNew(&new_bdmcLcLUniformGridEnvironmentcLcLGridNeighborMutexBuilder);
      instance.SetNewArray(&newArray_bdmcLcLUniformGridEnvironmentcLcLGridNeighborMutexBuilder);
      instance.SetDelete(&delete_bdmcLcLUniformGridEnvironmentcLcLGridNeighborMutexBuilder);
      instance.SetDeleteArray(&deleteArray_bdmcLcLUniformGridEnvironmentcLcLGridNeighborMutexBuilder);
      instance.SetDestructor(&destruct_bdmcLcLUniformGridEnvironmentcLcLGridNeighborMutexBuilder);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::bdm::UniformGridEnvironment::GridNeighborMutexBuilder*)
   {
      return GenerateInitInstanceLocal(static_cast<::bdm::UniformGridEnvironment::GridNeighborMutexBuilder*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::bdm::UniformGridEnvironment::GridNeighborMutexBuilder*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *bdmcLcLUniformGridEnvironmentcLcLGridNeighborMutexBuilder_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const ::bdm::UniformGridEnvironment::GridNeighborMutexBuilder*>(nullptr))->GetClass();
      bdmcLcLUniformGridEnvironmentcLcLGridNeighborMutexBuilder_TClassManip(theClass);
   return theClass;
   }

   static void bdmcLcLUniformGridEnvironmentcLcLGridNeighborMutexBuilder_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *bdmcLcLUniformGridEnvironmentcLcLGridNeighborMutexBuildercLcLGridNeighborMutex_Dictionary();
   static void bdmcLcLUniformGridEnvironmentcLcLGridNeighborMutexBuildercLcLGridNeighborMutex_TClassManip(TClass*);
   static void delete_bdmcLcLUniformGridEnvironmentcLcLGridNeighborMutexBuildercLcLGridNeighborMutex(void *p);
   static void deleteArray_bdmcLcLUniformGridEnvironmentcLcLGridNeighborMutexBuildercLcLGridNeighborMutex(void *p);
   static void destruct_bdmcLcLUniformGridEnvironmentcLcLGridNeighborMutexBuildercLcLGridNeighborMutex(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::bdm::UniformGridEnvironment::GridNeighborMutexBuilder::GridNeighborMutex*)
   {
      ::bdm::UniformGridEnvironment::GridNeighborMutexBuilder::GridNeighborMutex *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::bdm::UniformGridEnvironment::GridNeighborMutexBuilder::GridNeighborMutex));
      static ::ROOT::TGenericClassInfo 
         instance("bdm::UniformGridEnvironment::GridNeighborMutexBuilder::GridNeighborMutex", "core/environment/uniform_grid_environment.h", 545,
                  typeid(::bdm::UniformGridEnvironment::GridNeighborMutexBuilder::GridNeighborMutex), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &bdmcLcLUniformGridEnvironmentcLcLGridNeighborMutexBuildercLcLGridNeighborMutex_Dictionary, isa_proxy, 4,
                  sizeof(::bdm::UniformGridEnvironment::GridNeighborMutexBuilder::GridNeighborMutex) );
      instance.SetDelete(&delete_bdmcLcLUniformGridEnvironmentcLcLGridNeighborMutexBuildercLcLGridNeighborMutex);
      instance.SetDeleteArray(&deleteArray_bdmcLcLUniformGridEnvironmentcLcLGridNeighborMutexBuildercLcLGridNeighborMutex);
      instance.SetDestructor(&destruct_bdmcLcLUniformGridEnvironmentcLcLGridNeighborMutexBuildercLcLGridNeighborMutex);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::bdm::UniformGridEnvironment::GridNeighborMutexBuilder::GridNeighborMutex*)
   {
      return GenerateInitInstanceLocal(static_cast<::bdm::UniformGridEnvironment::GridNeighborMutexBuilder::GridNeighborMutex*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::bdm::UniformGridEnvironment::GridNeighborMutexBuilder::GridNeighborMutex*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *bdmcLcLUniformGridEnvironmentcLcLGridNeighborMutexBuildercLcLGridNeighborMutex_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const ::bdm::UniformGridEnvironment::GridNeighborMutexBuilder::GridNeighborMutex*>(nullptr))->GetClass();
      bdmcLcLUniformGridEnvironmentcLcLGridNeighborMutexBuildercLcLGridNeighborMutex_TClassManip(theClass);
   return theClass;
   }

   static void bdmcLcLUniformGridEnvironmentcLcLGridNeighborMutexBuildercLcLGridNeighborMutex_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *bdmcLcLBoundSpace_Dictionary();
   static void bdmcLcLBoundSpace_TClassManip(TClass*);
   static void *new_bdmcLcLBoundSpace(void *p = nullptr);
   static void *newArray_bdmcLcLBoundSpace(Long_t size, void *p);
   static void delete_bdmcLcLBoundSpace(void *p);
   static void deleteArray_bdmcLcLBoundSpace(void *p);
   static void destruct_bdmcLcLBoundSpace(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::bdm::BoundSpace*)
   {
      ::bdm::BoundSpace *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::bdm::BoundSpace));
      static ::ROOT::TGenericClassInfo 
         instance("bdm::BoundSpace", "core/operation/bound_space_op.h", 69,
                  typeid(::bdm::BoundSpace), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &bdmcLcLBoundSpace_Dictionary, isa_proxy, 4,
                  sizeof(::bdm::BoundSpace) );
      instance.SetNew(&new_bdmcLcLBoundSpace);
      instance.SetNewArray(&newArray_bdmcLcLBoundSpace);
      instance.SetDelete(&delete_bdmcLcLBoundSpace);
      instance.SetDeleteArray(&deleteArray_bdmcLcLBoundSpace);
      instance.SetDestructor(&destruct_bdmcLcLBoundSpace);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::bdm::BoundSpace*)
   {
      return GenerateInitInstanceLocal(static_cast<::bdm::BoundSpace*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::bdm::BoundSpace*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *bdmcLcLBoundSpace_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const ::bdm::BoundSpace*>(nullptr))->GetClass();
      bdmcLcLBoundSpace_TClassManip(theClass);
   return theClass;
   }

   static void bdmcLcLBoundSpace_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *bdmcLcLMechanicalForcesOp_Dictionary();
   static void bdmcLcLMechanicalForcesOp_TClassManip(TClass*);
   static void *new_bdmcLcLMechanicalForcesOp(void *p = nullptr);
   static void *newArray_bdmcLcLMechanicalForcesOp(Long_t size, void *p);
   static void delete_bdmcLcLMechanicalForcesOp(void *p);
   static void deleteArray_bdmcLcLMechanicalForcesOp(void *p);
   static void destruct_bdmcLcLMechanicalForcesOp(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::bdm::MechanicalForcesOp*)
   {
      ::bdm::MechanicalForcesOp *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::bdm::MechanicalForcesOp));
      static ::ROOT::TGenericClassInfo 
         instance("bdm::MechanicalForcesOp", "core/operation/mechanical_forces_op.h", 38,
                  typeid(::bdm::MechanicalForcesOp), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &bdmcLcLMechanicalForcesOp_Dictionary, isa_proxy, 4,
                  sizeof(::bdm::MechanicalForcesOp) );
      instance.SetNew(&new_bdmcLcLMechanicalForcesOp);
      instance.SetNewArray(&newArray_bdmcLcLMechanicalForcesOp);
      instance.SetDelete(&delete_bdmcLcLMechanicalForcesOp);
      instance.SetDeleteArray(&deleteArray_bdmcLcLMechanicalForcesOp);
      instance.SetDestructor(&destruct_bdmcLcLMechanicalForcesOp);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::bdm::MechanicalForcesOp*)
   {
      return GenerateInitInstanceLocal(static_cast<::bdm::MechanicalForcesOp*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::bdm::MechanicalForcesOp*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *bdmcLcLMechanicalForcesOp_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const ::bdm::MechanicalForcesOp*>(nullptr))->GetClass();
      bdmcLcLMechanicalForcesOp_TClassManip(theClass);
   return theClass;
   }

   static void bdmcLcLMechanicalForcesOp_TClassManip(TClass* ){
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
namespace bdm {
//______________________________________________________________________________
atomic_TClass_ptr Move::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *Move::Class_Name()
{
   return "bdm::Move";
}

//______________________________________________________________________________
const char *Move::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::bdm::Move*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int Move::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::bdm::Move*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Move::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::bdm::Move*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Move::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::bdm::Move*)nullptr)->GetClass(); }
   return fgIsA;
}

} // namespace bdm
namespace bdm {
//______________________________________________________________________________
atomic_TClass_ptr SimParam::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *SimParam::Class_Name()
{
   return "bdm::SimParam";
}

//______________________________________________________________________________
const char *SimParam::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::bdm::SimParam*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int SimParam::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::bdm::SimParam*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *SimParam::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::bdm::SimParam*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *SimParam::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::bdm::SimParam*)nullptr)->GetClass(); }
   return fgIsA;
}

} // namespace bdm
namespace ROOT {
   // Wrapper around operator delete
   static void delete_bdmcLcLFunctorlEvoidcObdmcLcLIteratorlEULong64_tgRmUgR(void *p) {
      delete (static_cast<::bdm::Functor<void,bdm::Iterator<ULong64_t>*>*>(p));
   }
   static void deleteArray_bdmcLcLFunctorlEvoidcObdmcLcLIteratorlEULong64_tgRmUgR(void *p) {
      delete [] (static_cast<::bdm::Functor<void,bdm::Iterator<ULong64_t>*>*>(p));
   }
   static void destruct_bdmcLcLFunctorlEvoidcObdmcLcLIteratorlEULong64_tgRmUgR(void *p) {
      typedef ::bdm::Functor<void,bdm::Iterator<ULong64_t>*> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::bdm::Functor<void,bdm::Iterator<ULong64_t>*>

namespace ROOT {
   // Wrappers around operator new
   static void *new_bdmcLcLFixedSizeVectorlEconstsPbdmcLcLUniformGridEnvironmentcLcLBoxmUcO27gR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) ::bdm::FixedSizeVector<const bdm::UniformGridEnvironment::Box*,27> : new ::bdm::FixedSizeVector<const bdm::UniformGridEnvironment::Box*,27>;
   }
   static void *newArray_bdmcLcLFixedSizeVectorlEconstsPbdmcLcLUniformGridEnvironmentcLcLBoxmUcO27gR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) ::bdm::FixedSizeVector<const bdm::UniformGridEnvironment::Box*,27>[nElements] : new ::bdm::FixedSizeVector<const bdm::UniformGridEnvironment::Box*,27>[nElements];
   }
   // Wrapper around operator delete
   static void delete_bdmcLcLFixedSizeVectorlEconstsPbdmcLcLUniformGridEnvironmentcLcLBoxmUcO27gR(void *p) {
      delete (static_cast<::bdm::FixedSizeVector<const bdm::UniformGridEnvironment::Box*,27>*>(p));
   }
   static void deleteArray_bdmcLcLFixedSizeVectorlEconstsPbdmcLcLUniformGridEnvironmentcLcLBoxmUcO27gR(void *p) {
      delete [] (static_cast<::bdm::FixedSizeVector<const bdm::UniformGridEnvironment::Box*,27>*>(p));
   }
   static void destruct_bdmcLcLFixedSizeVectorlEconstsPbdmcLcLUniformGridEnvironmentcLcLBoxmUcO27gR(void *p) {
      typedef ::bdm::FixedSizeVector<const bdm::UniformGridEnvironment::Box*,27> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::bdm::FixedSizeVector<const bdm::UniformGridEnvironment::Box*,27>

namespace ROOT {
   // Wrappers around operator new
   static void *new_bdmcLcLFixedSizeVectorlEULong64_tcO27gR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) ::bdm::FixedSizeVector<ULong64_t,27> : new ::bdm::FixedSizeVector<ULong64_t,27>;
   }
   static void *newArray_bdmcLcLFixedSizeVectorlEULong64_tcO27gR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) ::bdm::FixedSizeVector<ULong64_t,27>[nElements] : new ::bdm::FixedSizeVector<ULong64_t,27>[nElements];
   }
   // Wrapper around operator delete
   static void delete_bdmcLcLFixedSizeVectorlEULong64_tcO27gR(void *p) {
      delete (static_cast<::bdm::FixedSizeVector<ULong64_t,27>*>(p));
   }
   static void deleteArray_bdmcLcLFixedSizeVectorlEULong64_tcO27gR(void *p) {
      delete [] (static_cast<::bdm::FixedSizeVector<ULong64_t,27>*>(p));
   }
   static void destruct_bdmcLcLFixedSizeVectorlEULong64_tcO27gR(void *p) {
      typedef ::bdm::FixedSizeVector<ULong64_t,27> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::bdm::FixedSizeVector<ULong64_t,27>

namespace ROOT {
   // Wrappers around operator new
   static void *new_bdmcLcLFixedSizeVectorlEunsignedsPlongcO14gR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) ::bdm::FixedSizeVector<unsigned long,14> : new ::bdm::FixedSizeVector<unsigned long,14>;
   }
   static void *newArray_bdmcLcLFixedSizeVectorlEunsignedsPlongcO14gR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) ::bdm::FixedSizeVector<unsigned long,14>[nElements] : new ::bdm::FixedSizeVector<unsigned long,14>[nElements];
   }
   // Wrapper around operator delete
   static void delete_bdmcLcLFixedSizeVectorlEunsignedsPlongcO14gR(void *p) {
      delete (static_cast<::bdm::FixedSizeVector<unsigned long,14>*>(p));
   }
   static void deleteArray_bdmcLcLFixedSizeVectorlEunsignedsPlongcO14gR(void *p) {
      delete [] (static_cast<::bdm::FixedSizeVector<unsigned long,14>*>(p));
   }
   static void destruct_bdmcLcLFixedSizeVectorlEunsignedsPlongcO14gR(void *p) {
      typedef ::bdm::FixedSizeVector<unsigned long,14> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::bdm::FixedSizeVector<unsigned long,14>

namespace ROOT {
   // Wrappers around operator new
   static void *new_bdmcLcLAgentPointerlEbdmcLcLAgentgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) ::bdm::AgentPointer<bdm::Agent> : new ::bdm::AgentPointer<bdm::Agent>;
   }
   static void *newArray_bdmcLcLAgentPointerlEbdmcLcLAgentgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) ::bdm::AgentPointer<bdm::Agent>[nElements] : new ::bdm::AgentPointer<bdm::Agent>[nElements];
   }
   // Wrapper around operator delete
   static void delete_bdmcLcLAgentPointerlEbdmcLcLAgentgR(void *p) {
      delete (static_cast<::bdm::AgentPointer<bdm::Agent>*>(p));
   }
   static void deleteArray_bdmcLcLAgentPointerlEbdmcLcLAgentgR(void *p) {
      delete [] (static_cast<::bdm::AgentPointer<bdm::Agent>*>(p));
   }
   static void destruct_bdmcLcLAgentPointerlEbdmcLcLAgentgR(void *p) {
      typedef ::bdm::AgentPointer<bdm::Agent> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_bdmcLcLAgentPointerlEbdmcLcLAgentgR(TBuffer &buf, void *obj) {
      ((::bdm::AgentPointer<bdm::Agent>*)obj)->::bdm::AgentPointer<bdm::Agent>::Streamer(buf);
   }
} // end of namespace ROOT for class ::bdm::AgentPointer<bdm::Agent>

namespace ROOT {
   // Wrappers around operator new
   static void *new_bdmcLcLSharedDatalEULong64_tgRcLcLIterator(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) ::bdm::SharedData<ULong64_t>::Iterator : new ::bdm::SharedData<ULong64_t>::Iterator;
   }
   static void *newArray_bdmcLcLSharedDatalEULong64_tgRcLcLIterator(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) ::bdm::SharedData<ULong64_t>::Iterator[nElements] : new ::bdm::SharedData<ULong64_t>::Iterator[nElements];
   }
   // Wrapper around operator delete
   static void delete_bdmcLcLSharedDatalEULong64_tgRcLcLIterator(void *p) {
      delete (static_cast<::bdm::SharedData<ULong64_t>::Iterator*>(p));
   }
   static void deleteArray_bdmcLcLSharedDatalEULong64_tgRcLcLIterator(void *p) {
      delete [] (static_cast<::bdm::SharedData<ULong64_t>::Iterator*>(p));
   }
   static void destruct_bdmcLcLSharedDatalEULong64_tgRcLcLIterator(void *p) {
      typedef ::bdm::SharedData<ULong64_t>::Iterator current_t;
      (static_cast<current_t*>(p))->~current_t();
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
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) ::bdm::SharedData<double> : new ::bdm::SharedData<double>;
   }
   static void *newArray_bdmcLcLSharedDatalEdoublegR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) ::bdm::SharedData<double>[nElements] : new ::bdm::SharedData<double>[nElements];
   }
   // Wrapper around operator delete
   static void delete_bdmcLcLSharedDatalEdoublegR(void *p) {
      delete (static_cast<::bdm::SharedData<double>*>(p));
   }
   static void deleteArray_bdmcLcLSharedDatalEdoublegR(void *p) {
      delete [] (static_cast<::bdm::SharedData<double>*>(p));
   }
   static void destruct_bdmcLcLSharedDatalEdoublegR(void *p) {
      typedef ::bdm::SharedData<double> current_t;
      (static_cast<current_t*>(p))->~current_t();
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
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) ::bdm::SharedData<float> : new ::bdm::SharedData<float>;
   }
   static void *newArray_bdmcLcLSharedDatalEfloatgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) ::bdm::SharedData<float>[nElements] : new ::bdm::SharedData<float>[nElements];
   }
   // Wrapper around operator delete
   static void delete_bdmcLcLSharedDatalEfloatgR(void *p) {
      delete (static_cast<::bdm::SharedData<float>*>(p));
   }
   static void deleteArray_bdmcLcLSharedDatalEfloatgR(void *p) {
      delete [] (static_cast<::bdm::SharedData<float>*>(p));
   }
   static void destruct_bdmcLcLSharedDatalEfloatgR(void *p) {
      typedef ::bdm::SharedData<float> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::bdm::SharedData<float>

namespace ROOT {
   // Wrappers around operator new
   static void *new_bdmcLcLProgressBar(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) ::bdm::ProgressBar : new ::bdm::ProgressBar;
   }
   static void *newArray_bdmcLcLProgressBar(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) ::bdm::ProgressBar[nElements] : new ::bdm::ProgressBar[nElements];
   }
   // Wrapper around operator delete
   static void delete_bdmcLcLProgressBar(void *p) {
      delete (static_cast<::bdm::ProgressBar*>(p));
   }
   static void deleteArray_bdmcLcLProgressBar(void *p) {
      delete [] (static_cast<::bdm::ProgressBar*>(p));
   }
   static void destruct_bdmcLcLProgressBar(void *p) {
      typedef ::bdm::ProgressBar current_t;
      (static_cast<current_t*>(p))->~current_t();
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
      delete (static_cast<::bdm::VectorField*>(p));
   }
   static void deleteArray_bdmcLcLVectorField(void *p) {
      delete [] (static_cast<::bdm::VectorField*>(p));
   }
   static void destruct_bdmcLcLVectorField(void *p) {
      typedef ::bdm::VectorField current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::bdm::VectorField

namespace ROOT {
   // Wrappers around operator new
   static void *new_bdmcLcLUniformGridEnvironmentcLcLBox(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) ::bdm::UniformGridEnvironment::Box : new ::bdm::UniformGridEnvironment::Box;
   }
   static void *newArray_bdmcLcLUniformGridEnvironmentcLcLBox(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) ::bdm::UniformGridEnvironment::Box[nElements] : new ::bdm::UniformGridEnvironment::Box[nElements];
   }
   // Wrapper around operator delete
   static void delete_bdmcLcLUniformGridEnvironmentcLcLBox(void *p) {
      delete (static_cast<::bdm::UniformGridEnvironment::Box*>(p));
   }
   static void deleteArray_bdmcLcLUniformGridEnvironmentcLcLBox(void *p) {
      delete [] (static_cast<::bdm::UniformGridEnvironment::Box*>(p));
   }
   static void destruct_bdmcLcLUniformGridEnvironmentcLcLBox(void *p) {
      typedef ::bdm::UniformGridEnvironment::Box current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::bdm::UniformGridEnvironment::Box

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
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) ::bdm::Moving_cell( (TRootIOCtor *)nullptr ) : new ::bdm::Moving_cell( (TRootIOCtor *)nullptr );
   }
   // Wrapper around operator delete
   static void delete_bdmcLcLMoving_cell(void *p) {
      delete (static_cast<::bdm::Moving_cell*>(p));
   }
   static void deleteArray_bdmcLcLMoving_cell(void *p) {
      delete [] (static_cast<::bdm::Moving_cell*>(p));
   }
   static void destruct_bdmcLcLMoving_cell(void *p) {
      typedef ::bdm::Moving_cell current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::bdm::Moving_cell

namespace bdm {
//______________________________________________________________________________
void Move::Streamer(TBuffer &R__b)
{
   // Stream an object of class bdm::Move.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(bdm::Move::Class(),this);
   } else {
      R__b.WriteClassBuffer(bdm::Move::Class(),this);
   }
}

} // namespace bdm
namespace ROOT {
   // Wrappers around operator new
   static void *new_bdmcLcLMove(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) ::bdm::Move : new ::bdm::Move;
   }
   static void *newArray_bdmcLcLMove(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) ::bdm::Move[nElements] : new ::bdm::Move[nElements];
   }
   // Wrapper around operator delete
   static void delete_bdmcLcLMove(void *p) {
      delete (static_cast<::bdm::Move*>(p));
   }
   static void deleteArray_bdmcLcLMove(void *p) {
      delete [] (static_cast<::bdm::Move*>(p));
   }
   static void destruct_bdmcLcLMove(void *p) {
      typedef ::bdm::Move current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::bdm::Move

namespace ROOT {
   // Wrappers around operator new
   static void *new_bdmcLcLCellCellForce(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) ::bdm::CellCellForce : new ::bdm::CellCellForce;
   }
   static void *newArray_bdmcLcLCellCellForce(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) ::bdm::CellCellForce[nElements] : new ::bdm::CellCellForce[nElements];
   }
   // Wrapper around operator delete
   static void delete_bdmcLcLCellCellForce(void *p) {
      delete (static_cast<::bdm::CellCellForce*>(p));
   }
   static void deleteArray_bdmcLcLCellCellForce(void *p) {
      delete [] (static_cast<::bdm::CellCellForce*>(p));
   }
   static void destruct_bdmcLcLCellCellForce(void *p) {
      typedef ::bdm::CellCellForce current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::bdm::CellCellForce

namespace ROOT {
   // Wrappers around operator new
   static void *new_bdmcLcLDissipativeForce(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) ::bdm::DissipativeForce : new ::bdm::DissipativeForce;
   }
   static void *newArray_bdmcLcLDissipativeForce(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) ::bdm::DissipativeForce[nElements] : new ::bdm::DissipativeForce[nElements];
   }
   // Wrapper around operator delete
   static void delete_bdmcLcLDissipativeForce(void *p) {
      delete (static_cast<::bdm::DissipativeForce*>(p));
   }
   static void deleteArray_bdmcLcLDissipativeForce(void *p) {
      delete [] (static_cast<::bdm::DissipativeForce*>(p));
   }
   static void destruct_bdmcLcLDissipativeForce(void *p) {
      typedef ::bdm::DissipativeForce current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::bdm::DissipativeForce

namespace ROOT {
   // Wrappers around operator new
   static void *new_bdmcLcLTrackPosition(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) ::bdm::TrackPosition : new ::bdm::TrackPosition;
   }
   static void *newArray_bdmcLcLTrackPosition(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) ::bdm::TrackPosition[nElements] : new ::bdm::TrackPosition[nElements];
   }
   // Wrapper around operator delete
   static void delete_bdmcLcLTrackPosition(void *p) {
      delete (static_cast<::bdm::TrackPosition*>(p));
   }
   static void deleteArray_bdmcLcLTrackPosition(void *p) {
      delete [] (static_cast<::bdm::TrackPosition*>(p));
   }
   static void destruct_bdmcLcLTrackPosition(void *p) {
      typedef ::bdm::TrackPosition current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::bdm::TrackPosition

namespace bdm {
//______________________________________________________________________________
void SimParam::Streamer(TBuffer &R__b)
{
   // Stream an object of class bdm::SimParam.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(bdm::SimParam::Class(),this);
   } else {
      R__b.WriteClassBuffer(bdm::SimParam::Class(),this);
   }
}

} // namespace bdm
namespace ROOT {
   // Wrappers around operator new
   static void *new_bdmcLcLSimParam(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) ::bdm::SimParam : new ::bdm::SimParam;
   }
   static void *newArray_bdmcLcLSimParam(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) ::bdm::SimParam[nElements] : new ::bdm::SimParam[nElements];
   }
   // Wrapper around operator delete
   static void delete_bdmcLcLSimParam(void *p) {
      delete (static_cast<::bdm::SimParam*>(p));
   }
   static void deleteArray_bdmcLcLSimParam(void *p) {
      delete [] (static_cast<::bdm::SimParam*>(p));
   }
   static void destruct_bdmcLcLSimParam(void *p) {
      typedef ::bdm::SimParam current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::bdm::SimParam

namespace ROOT {
   // Wrappers around operator new
   static void *new_bdmcLcLAgentVectorlEbdmcLcLAgentHandlegR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) ::bdm::AgentVector<bdm::AgentHandle> : new ::bdm::AgentVector<bdm::AgentHandle>;
   }
   static void *newArray_bdmcLcLAgentVectorlEbdmcLcLAgentHandlegR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) ::bdm::AgentVector<bdm::AgentHandle>[nElements] : new ::bdm::AgentVector<bdm::AgentHandle>[nElements];
   }
   // Wrapper around operator delete
   static void delete_bdmcLcLAgentVectorlEbdmcLcLAgentHandlegR(void *p) {
      delete (static_cast<::bdm::AgentVector<bdm::AgentHandle>*>(p));
   }
   static void deleteArray_bdmcLcLAgentVectorlEbdmcLcLAgentHandlegR(void *p) {
      delete [] (static_cast<::bdm::AgentVector<bdm::AgentHandle>*>(p));
   }
   static void destruct_bdmcLcLAgentVectorlEbdmcLcLAgentHandlegR(void *p) {
      typedef ::bdm::AgentVector<bdm::AgentHandle> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::bdm::AgentVector<bdm::AgentHandle>

namespace ROOT {
   // Wrappers around operator new
   static void *new_bdmcLcLMortonOrder(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) ::bdm::MortonOrder : new ::bdm::MortonOrder;
   }
   static void *newArray_bdmcLcLMortonOrder(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) ::bdm::MortonOrder[nElements] : new ::bdm::MortonOrder[nElements];
   }
   // Wrapper around operator delete
   static void delete_bdmcLcLMortonOrder(void *p) {
      delete (static_cast<::bdm::MortonOrder*>(p));
   }
   static void deleteArray_bdmcLcLMortonOrder(void *p) {
      delete [] (static_cast<::bdm::MortonOrder*>(p));
   }
   static void destruct_bdmcLcLMortonOrder(void *p) {
      typedef ::bdm::MortonOrder current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::bdm::MortonOrder

namespace ROOT {
   // Wrapper around operator delete
   static void delete_bdmcLcLUniformGridEnvironmentcLcLBoxcLcLIterator(void *p) {
      delete (static_cast<::bdm::UniformGridEnvironment::Box::Iterator*>(p));
   }
   static void deleteArray_bdmcLcLUniformGridEnvironmentcLcLBoxcLcLIterator(void *p) {
      delete [] (static_cast<::bdm::UniformGridEnvironment::Box::Iterator*>(p));
   }
   static void destruct_bdmcLcLUniformGridEnvironmentcLcLBoxcLcLIterator(void *p) {
      typedef ::bdm::UniformGridEnvironment::Box::Iterator current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::bdm::UniformGridEnvironment::Box::Iterator

namespace ROOT {
   // Wrapper around operator delete
   static void delete_bdmcLcLUniformGridEnvironmentcLcLNeighborIterator(void *p) {
      delete (static_cast<::bdm::UniformGridEnvironment::NeighborIterator*>(p));
   }
   static void deleteArray_bdmcLcLUniformGridEnvironmentcLcLNeighborIterator(void *p) {
      delete [] (static_cast<::bdm::UniformGridEnvironment::NeighborIterator*>(p));
   }
   static void destruct_bdmcLcLUniformGridEnvironmentcLcLNeighborIterator(void *p) {
      typedef ::bdm::UniformGridEnvironment::NeighborIterator current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::bdm::UniformGridEnvironment::NeighborIterator

namespace ROOT {
   // Wrapper around operator delete
   static void delete_bdmcLcLUniformGridEnvironmentcLcLAssignToBoxesFunctor(void *p) {
      delete (static_cast<::bdm::UniformGridEnvironment::AssignToBoxesFunctor*>(p));
   }
   static void deleteArray_bdmcLcLUniformGridEnvironmentcLcLAssignToBoxesFunctor(void *p) {
      delete [] (static_cast<::bdm::UniformGridEnvironment::AssignToBoxesFunctor*>(p));
   }
   static void destruct_bdmcLcLUniformGridEnvironmentcLcLAssignToBoxesFunctor(void *p) {
      typedef ::bdm::UniformGridEnvironment::AssignToBoxesFunctor current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::bdm::UniformGridEnvironment::AssignToBoxesFunctor

namespace ROOT {
   // Wrappers around operator new
   static void *new_bdmcLcLUniformGridEnvironmentcLcLGridNeighborMutexBuilder(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) ::bdm::UniformGridEnvironment::GridNeighborMutexBuilder : new ::bdm::UniformGridEnvironment::GridNeighborMutexBuilder;
   }
   static void *newArray_bdmcLcLUniformGridEnvironmentcLcLGridNeighborMutexBuilder(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) ::bdm::UniformGridEnvironment::GridNeighborMutexBuilder[nElements] : new ::bdm::UniformGridEnvironment::GridNeighborMutexBuilder[nElements];
   }
   // Wrapper around operator delete
   static void delete_bdmcLcLUniformGridEnvironmentcLcLGridNeighborMutexBuilder(void *p) {
      delete (static_cast<::bdm::UniformGridEnvironment::GridNeighborMutexBuilder*>(p));
   }
   static void deleteArray_bdmcLcLUniformGridEnvironmentcLcLGridNeighborMutexBuilder(void *p) {
      delete [] (static_cast<::bdm::UniformGridEnvironment::GridNeighborMutexBuilder*>(p));
   }
   static void destruct_bdmcLcLUniformGridEnvironmentcLcLGridNeighborMutexBuilder(void *p) {
      typedef ::bdm::UniformGridEnvironment::GridNeighborMutexBuilder current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::bdm::UniformGridEnvironment::GridNeighborMutexBuilder

namespace ROOT {
   // Wrapper around operator delete
   static void delete_bdmcLcLUniformGridEnvironmentcLcLGridNeighborMutexBuildercLcLGridNeighborMutex(void *p) {
      delete (static_cast<::bdm::UniformGridEnvironment::GridNeighborMutexBuilder::GridNeighborMutex*>(p));
   }
   static void deleteArray_bdmcLcLUniformGridEnvironmentcLcLGridNeighborMutexBuildercLcLGridNeighborMutex(void *p) {
      delete [] (static_cast<::bdm::UniformGridEnvironment::GridNeighborMutexBuilder::GridNeighborMutex*>(p));
   }
   static void destruct_bdmcLcLUniformGridEnvironmentcLcLGridNeighborMutexBuildercLcLGridNeighborMutex(void *p) {
      typedef ::bdm::UniformGridEnvironment::GridNeighborMutexBuilder::GridNeighborMutex current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::bdm::UniformGridEnvironment::GridNeighborMutexBuilder::GridNeighborMutex

namespace ROOT {
   // Wrappers around operator new
   static void *new_bdmcLcLBoundSpace(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) ::bdm::BoundSpace : new ::bdm::BoundSpace;
   }
   static void *newArray_bdmcLcLBoundSpace(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) ::bdm::BoundSpace[nElements] : new ::bdm::BoundSpace[nElements];
   }
   // Wrapper around operator delete
   static void delete_bdmcLcLBoundSpace(void *p) {
      delete (static_cast<::bdm::BoundSpace*>(p));
   }
   static void deleteArray_bdmcLcLBoundSpace(void *p) {
      delete [] (static_cast<::bdm::BoundSpace*>(p));
   }
   static void destruct_bdmcLcLBoundSpace(void *p) {
      typedef ::bdm::BoundSpace current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::bdm::BoundSpace

namespace ROOT {
   // Wrappers around operator new
   static void *new_bdmcLcLMechanicalForcesOp(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) ::bdm::MechanicalForcesOp : new ::bdm::MechanicalForcesOp;
   }
   static void *newArray_bdmcLcLMechanicalForcesOp(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) ::bdm::MechanicalForcesOp[nElements] : new ::bdm::MechanicalForcesOp[nElements];
   }
   // Wrapper around operator delete
   static void delete_bdmcLcLMechanicalForcesOp(void *p) {
      delete (static_cast<::bdm::MechanicalForcesOp*>(p));
   }
   static void deleteArray_bdmcLcLMechanicalForcesOp(void *p) {
      delete [] (static_cast<::bdm::MechanicalForcesOp*>(p));
   }
   static void destruct_bdmcLcLMechanicalForcesOp(void *p) {
      typedef ::bdm::MechanicalForcesOp current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::bdm::MechanicalForcesOp

namespace ROOT {
   static TClass *vectorlEbdmcLcLUniformGridEnvironmentcLcLGridNeighborMutexBuildercLcLMutexWrappergR_Dictionary();
   static void vectorlEbdmcLcLUniformGridEnvironmentcLcLGridNeighborMutexBuildercLcLMutexWrappergR_TClassManip(TClass*);
   static void *new_vectorlEbdmcLcLUniformGridEnvironmentcLcLGridNeighborMutexBuildercLcLMutexWrappergR(void *p = nullptr);
   static void *newArray_vectorlEbdmcLcLUniformGridEnvironmentcLcLGridNeighborMutexBuildercLcLMutexWrappergR(Long_t size, void *p);
   static void delete_vectorlEbdmcLcLUniformGridEnvironmentcLcLGridNeighborMutexBuildercLcLMutexWrappergR(void *p);
   static void deleteArray_vectorlEbdmcLcLUniformGridEnvironmentcLcLGridNeighborMutexBuildercLcLMutexWrappergR(void *p);
   static void destruct_vectorlEbdmcLcLUniformGridEnvironmentcLcLGridNeighborMutexBuildercLcLMutexWrappergR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<bdm::UniformGridEnvironment::GridNeighborMutexBuilder::MutexWrapper>*)
   {
      vector<bdm::UniformGridEnvironment::GridNeighborMutexBuilder::MutexWrapper> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<bdm::UniformGridEnvironment::GridNeighborMutexBuilder::MutexWrapper>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<bdm::UniformGridEnvironment::GridNeighborMutexBuilder::MutexWrapper>", -2, "vector", 493,
                  typeid(vector<bdm::UniformGridEnvironment::GridNeighborMutexBuilder::MutexWrapper>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEbdmcLcLUniformGridEnvironmentcLcLGridNeighborMutexBuildercLcLMutexWrappergR_Dictionary, isa_proxy, 4,
                  sizeof(vector<bdm::UniformGridEnvironment::GridNeighborMutexBuilder::MutexWrapper>) );
      instance.SetNew(&new_vectorlEbdmcLcLUniformGridEnvironmentcLcLGridNeighborMutexBuildercLcLMutexWrappergR);
      instance.SetNewArray(&newArray_vectorlEbdmcLcLUniformGridEnvironmentcLcLGridNeighborMutexBuildercLcLMutexWrappergR);
      instance.SetDelete(&delete_vectorlEbdmcLcLUniformGridEnvironmentcLcLGridNeighborMutexBuildercLcLMutexWrappergR);
      instance.SetDeleteArray(&deleteArray_vectorlEbdmcLcLUniformGridEnvironmentcLcLGridNeighborMutexBuildercLcLMutexWrappergR);
      instance.SetDestructor(&destruct_vectorlEbdmcLcLUniformGridEnvironmentcLcLGridNeighborMutexBuildercLcLMutexWrappergR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<bdm::UniformGridEnvironment::GridNeighborMutexBuilder::MutexWrapper> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<bdm::UniformGridEnvironment::GridNeighborMutexBuilder::MutexWrapper>","std::__1::vector<bdm::UniformGridEnvironment::GridNeighborMutexBuilder::MutexWrapper, std::__1::allocator<bdm::UniformGridEnvironment::GridNeighborMutexBuilder::MutexWrapper>>"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<bdm::UniformGridEnvironment::GridNeighborMutexBuilder::MutexWrapper>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEbdmcLcLUniformGridEnvironmentcLcLGridNeighborMutexBuildercLcLMutexWrappergR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<bdm::UniformGridEnvironment::GridNeighborMutexBuilder::MutexWrapper>*>(nullptr))->GetClass();
      vectorlEbdmcLcLUniformGridEnvironmentcLcLGridNeighborMutexBuildercLcLMutexWrappergR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEbdmcLcLUniformGridEnvironmentcLcLGridNeighborMutexBuildercLcLMutexWrappergR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEbdmcLcLUniformGridEnvironmentcLcLGridNeighborMutexBuildercLcLMutexWrappergR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<bdm::UniformGridEnvironment::GridNeighborMutexBuilder::MutexWrapper> : new vector<bdm::UniformGridEnvironment::GridNeighborMutexBuilder::MutexWrapper>;
   }
   static void *newArray_vectorlEbdmcLcLUniformGridEnvironmentcLcLGridNeighborMutexBuildercLcLMutexWrappergR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<bdm::UniformGridEnvironment::GridNeighborMutexBuilder::MutexWrapper>[nElements] : new vector<bdm::UniformGridEnvironment::GridNeighborMutexBuilder::MutexWrapper>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEbdmcLcLUniformGridEnvironmentcLcLGridNeighborMutexBuildercLcLMutexWrappergR(void *p) {
      delete (static_cast<vector<bdm::UniformGridEnvironment::GridNeighborMutexBuilder::MutexWrapper>*>(p));
   }
   static void deleteArray_vectorlEbdmcLcLUniformGridEnvironmentcLcLGridNeighborMutexBuildercLcLMutexWrappergR(void *p) {
      delete [] (static_cast<vector<bdm::UniformGridEnvironment::GridNeighborMutexBuilder::MutexWrapper>*>(p));
   }
   static void destruct_vectorlEbdmcLcLUniformGridEnvironmentcLcLGridNeighborMutexBuildercLcLMutexWrappergR(void *p) {
      typedef vector<bdm::UniformGridEnvironment::GridNeighborMutexBuilder::MutexWrapper> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<bdm::UniformGridEnvironment::GridNeighborMutexBuilder::MutexWrapper>

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
         instance("vector<bdm::Spinlock*>", -2, "vector", 493,
                  typeid(vector<bdm::Spinlock*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEbdmcLcLSpinlockmUgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<bdm::Spinlock*>) );
      instance.SetNew(&new_vectorlEbdmcLcLSpinlockmUgR);
      instance.SetNewArray(&newArray_vectorlEbdmcLcLSpinlockmUgR);
      instance.SetDelete(&delete_vectorlEbdmcLcLSpinlockmUgR);
      instance.SetDeleteArray(&deleteArray_vectorlEbdmcLcLSpinlockmUgR);
      instance.SetDestructor(&destruct_vectorlEbdmcLcLSpinlockmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<bdm::Spinlock*> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<bdm::Spinlock*>","std::__1::vector<bdm::Spinlock*, std::__1::allocator<bdm::Spinlock*>>"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<bdm::Spinlock*>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEbdmcLcLSpinlockmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<bdm::Spinlock*>*>(nullptr))->GetClass();
      vectorlEbdmcLcLSpinlockmUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEbdmcLcLSpinlockmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEbdmcLcLSpinlockmUgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<bdm::Spinlock*> : new vector<bdm::Spinlock*>;
   }
   static void *newArray_vectorlEbdmcLcLSpinlockmUgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<bdm::Spinlock*>[nElements] : new vector<bdm::Spinlock*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEbdmcLcLSpinlockmUgR(void *p) {
      delete (static_cast<vector<bdm::Spinlock*>*>(p));
   }
   static void deleteArray_vectorlEbdmcLcLSpinlockmUgR(void *p) {
      delete [] (static_cast<vector<bdm::Spinlock*>*>(p));
   }
   static void destruct_vectorlEbdmcLcLSpinlockmUgR(void *p) {
      typedef vector<bdm::Spinlock*> current_t;
      (static_cast<current_t*>(p))->~current_t();
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
         instance("vector<bdm::SharedData<vector<bdm::AgentUid> >::AlignedT>", -2, "vector", 493,
                  typeid(vector<bdm::SharedData<vector<bdm::AgentUid> >::AlignedT>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEbdmcLcLSharedDatalEvectorlEbdmcLcLAgentUidgRsPgRcLcLAlignedTgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<bdm::SharedData<vector<bdm::AgentUid> >::AlignedT>) );
      instance.SetNew(&new_vectorlEbdmcLcLSharedDatalEvectorlEbdmcLcLAgentUidgRsPgRcLcLAlignedTgR);
      instance.SetNewArray(&newArray_vectorlEbdmcLcLSharedDatalEvectorlEbdmcLcLAgentUidgRsPgRcLcLAlignedTgR);
      instance.SetDelete(&delete_vectorlEbdmcLcLSharedDatalEvectorlEbdmcLcLAgentUidgRsPgRcLcLAlignedTgR);
      instance.SetDeleteArray(&deleteArray_vectorlEbdmcLcLSharedDatalEvectorlEbdmcLcLAgentUidgRsPgRcLcLAlignedTgR);
      instance.SetDestructor(&destruct_vectorlEbdmcLcLSharedDatalEvectorlEbdmcLcLAgentUidgRsPgRcLcLAlignedTgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<bdm::SharedData<vector<bdm::AgentUid> >::AlignedT> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<bdm::SharedData<vector<bdm::AgentUid> >::AlignedT>","std::__1::vector<bdm::SharedData<std::__1::vector<bdm::AgentUid, std::__1::allocator<bdm::AgentUid>>>::AlignedT, std::__1::allocator<bdm::SharedData<std::__1::vector<bdm::AgentUid, std::__1::allocator<bdm::AgentUid>>>::AlignedT>>"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<bdm::SharedData<vector<bdm::AgentUid> >::AlignedT>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEbdmcLcLSharedDatalEvectorlEbdmcLcLAgentUidgRsPgRcLcLAlignedTgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<bdm::SharedData<vector<bdm::AgentUid> >::AlignedT>*>(nullptr))->GetClass();
      vectorlEbdmcLcLSharedDatalEvectorlEbdmcLcLAgentUidgRsPgRcLcLAlignedTgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEbdmcLcLSharedDatalEvectorlEbdmcLcLAgentUidgRsPgRcLcLAlignedTgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEbdmcLcLSharedDatalEvectorlEbdmcLcLAgentUidgRsPgRcLcLAlignedTgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<bdm::SharedData<vector<bdm::AgentUid> >::AlignedT> : new vector<bdm::SharedData<vector<bdm::AgentUid> >::AlignedT>;
   }
   static void *newArray_vectorlEbdmcLcLSharedDatalEvectorlEbdmcLcLAgentUidgRsPgRcLcLAlignedTgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<bdm::SharedData<vector<bdm::AgentUid> >::AlignedT>[nElements] : new vector<bdm::SharedData<vector<bdm::AgentUid> >::AlignedT>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEbdmcLcLSharedDatalEvectorlEbdmcLcLAgentUidgRsPgRcLcLAlignedTgR(void *p) {
      delete (static_cast<vector<bdm::SharedData<vector<bdm::AgentUid> >::AlignedT>*>(p));
   }
   static void deleteArray_vectorlEbdmcLcLSharedDatalEvectorlEbdmcLcLAgentUidgRsPgRcLcLAlignedTgR(void *p) {
      delete [] (static_cast<vector<bdm::SharedData<vector<bdm::AgentUid> >::AlignedT>*>(p));
   }
   static void destruct_vectorlEbdmcLcLSharedDatalEvectorlEbdmcLcLAgentUidgRsPgRcLcLAlignedTgR(void *p) {
      typedef vector<bdm::SharedData<vector<bdm::AgentUid> >::AlignedT> current_t;
      (static_cast<current_t*>(p))->~current_t();
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
         instance("vector<bdm::SharedData<float>::AlignedT>", -2, "vector", 493,
                  typeid(vector<bdm::SharedData<float>::AlignedT>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEbdmcLcLSharedDatalEfloatgRcLcLAlignedTgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<bdm::SharedData<float>::AlignedT>) );
      instance.SetNew(&new_vectorlEbdmcLcLSharedDatalEfloatgRcLcLAlignedTgR);
      instance.SetNewArray(&newArray_vectorlEbdmcLcLSharedDatalEfloatgRcLcLAlignedTgR);
      instance.SetDelete(&delete_vectorlEbdmcLcLSharedDatalEfloatgRcLcLAlignedTgR);
      instance.SetDeleteArray(&deleteArray_vectorlEbdmcLcLSharedDatalEfloatgRcLcLAlignedTgR);
      instance.SetDestructor(&destruct_vectorlEbdmcLcLSharedDatalEfloatgRcLcLAlignedTgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<bdm::SharedData<float>::AlignedT> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<bdm::SharedData<float>::AlignedT>","std::__1::vector<bdm::SharedData<float>::AlignedT, std::__1::allocator<bdm::SharedData<float>::AlignedT>>"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<bdm::SharedData<float>::AlignedT>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEbdmcLcLSharedDatalEfloatgRcLcLAlignedTgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<bdm::SharedData<float>::AlignedT>*>(nullptr))->GetClass();
      vectorlEbdmcLcLSharedDatalEfloatgRcLcLAlignedTgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEbdmcLcLSharedDatalEfloatgRcLcLAlignedTgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEbdmcLcLSharedDatalEfloatgRcLcLAlignedTgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<bdm::SharedData<float>::AlignedT> : new vector<bdm::SharedData<float>::AlignedT>;
   }
   static void *newArray_vectorlEbdmcLcLSharedDatalEfloatgRcLcLAlignedTgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<bdm::SharedData<float>::AlignedT>[nElements] : new vector<bdm::SharedData<float>::AlignedT>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEbdmcLcLSharedDatalEfloatgRcLcLAlignedTgR(void *p) {
      delete (static_cast<vector<bdm::SharedData<float>::AlignedT>*>(p));
   }
   static void deleteArray_vectorlEbdmcLcLSharedDatalEfloatgRcLcLAlignedTgR(void *p) {
      delete [] (static_cast<vector<bdm::SharedData<float>::AlignedT>*>(p));
   }
   static void destruct_vectorlEbdmcLcLSharedDatalEfloatgRcLcLAlignedTgR(void *p) {
      typedef vector<bdm::SharedData<float>::AlignedT> current_t;
      (static_cast<current_t*>(p))->~current_t();
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
         instance("vector<bdm::SharedData<double>::AlignedT>", -2, "vector", 493,
                  typeid(vector<bdm::SharedData<double>::AlignedT>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEbdmcLcLSharedDatalEdoublegRcLcLAlignedTgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<bdm::SharedData<double>::AlignedT>) );
      instance.SetNew(&new_vectorlEbdmcLcLSharedDatalEdoublegRcLcLAlignedTgR);
      instance.SetNewArray(&newArray_vectorlEbdmcLcLSharedDatalEdoublegRcLcLAlignedTgR);
      instance.SetDelete(&delete_vectorlEbdmcLcLSharedDatalEdoublegRcLcLAlignedTgR);
      instance.SetDeleteArray(&deleteArray_vectorlEbdmcLcLSharedDatalEdoublegRcLcLAlignedTgR);
      instance.SetDestructor(&destruct_vectorlEbdmcLcLSharedDatalEdoublegRcLcLAlignedTgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<bdm::SharedData<double>::AlignedT> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<bdm::SharedData<double>::AlignedT>","std::__1::vector<bdm::SharedData<double>::AlignedT, std::__1::allocator<bdm::SharedData<double>::AlignedT>>"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<bdm::SharedData<double>::AlignedT>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEbdmcLcLSharedDatalEdoublegRcLcLAlignedTgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<bdm::SharedData<double>::AlignedT>*>(nullptr))->GetClass();
      vectorlEbdmcLcLSharedDatalEdoublegRcLcLAlignedTgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEbdmcLcLSharedDatalEdoublegRcLcLAlignedTgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEbdmcLcLSharedDatalEdoublegRcLcLAlignedTgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<bdm::SharedData<double>::AlignedT> : new vector<bdm::SharedData<double>::AlignedT>;
   }
   static void *newArray_vectorlEbdmcLcLSharedDatalEdoublegRcLcLAlignedTgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<bdm::SharedData<double>::AlignedT>[nElements] : new vector<bdm::SharedData<double>::AlignedT>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEbdmcLcLSharedDatalEdoublegRcLcLAlignedTgR(void *p) {
      delete (static_cast<vector<bdm::SharedData<double>::AlignedT>*>(p));
   }
   static void deleteArray_vectorlEbdmcLcLSharedDatalEdoublegRcLcLAlignedTgR(void *p) {
      delete [] (static_cast<vector<bdm::SharedData<double>::AlignedT>*>(p));
   }
   static void destruct_vectorlEbdmcLcLSharedDatalEdoublegRcLcLAlignedTgR(void *p) {
      typedef vector<bdm::SharedData<double>::AlignedT> current_t;
      (static_cast<current_t*>(p))->~current_t();
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
         instance("vector<bdm::SharedData<bdm::MathArray<double,4> >::AlignedT>", -2, "vector", 493,
                  typeid(vector<bdm::SharedData<bdm::MathArray<double,4> >::AlignedT>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO4gRsPgRcLcLAlignedTgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<bdm::SharedData<bdm::MathArray<double,4> >::AlignedT>) );
      instance.SetNew(&new_vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO4gRsPgRcLcLAlignedTgR);
      instance.SetNewArray(&newArray_vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO4gRsPgRcLcLAlignedTgR);
      instance.SetDelete(&delete_vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO4gRsPgRcLcLAlignedTgR);
      instance.SetDeleteArray(&deleteArray_vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO4gRsPgRcLcLAlignedTgR);
      instance.SetDestructor(&destruct_vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO4gRsPgRcLcLAlignedTgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<bdm::SharedData<bdm::MathArray<double,4> >::AlignedT> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<bdm::SharedData<bdm::MathArray<double,4> >::AlignedT>","std::__1::vector<bdm::SharedData<bdm::MathArray<double, 4ul>>::AlignedT, std::__1::allocator<bdm::SharedData<bdm::MathArray<double, 4ul>>::AlignedT>>"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<bdm::SharedData<bdm::MathArray<double,4> >::AlignedT>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO4gRsPgRcLcLAlignedTgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<bdm::SharedData<bdm::MathArray<double,4> >::AlignedT>*>(nullptr))->GetClass();
      vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO4gRsPgRcLcLAlignedTgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO4gRsPgRcLcLAlignedTgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO4gRsPgRcLcLAlignedTgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<bdm::SharedData<bdm::MathArray<double,4> >::AlignedT> : new vector<bdm::SharedData<bdm::MathArray<double,4> >::AlignedT>;
   }
   static void *newArray_vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO4gRsPgRcLcLAlignedTgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<bdm::SharedData<bdm::MathArray<double,4> >::AlignedT>[nElements] : new vector<bdm::SharedData<bdm::MathArray<double,4> >::AlignedT>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO4gRsPgRcLcLAlignedTgR(void *p) {
      delete (static_cast<vector<bdm::SharedData<bdm::MathArray<double,4> >::AlignedT>*>(p));
   }
   static void deleteArray_vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO4gRsPgRcLcLAlignedTgR(void *p) {
      delete [] (static_cast<vector<bdm::SharedData<bdm::MathArray<double,4> >::AlignedT>*>(p));
   }
   static void destruct_vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO4gRsPgRcLcLAlignedTgR(void *p) {
      typedef vector<bdm::SharedData<bdm::MathArray<double,4> >::AlignedT> current_t;
      (static_cast<current_t*>(p))->~current_t();
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
         instance("vector<bdm::SharedData<bdm::MathArray<double,3> >::AlignedT>", -2, "vector", 493,
                  typeid(vector<bdm::SharedData<bdm::MathArray<double,3> >::AlignedT>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO3gRsPgRcLcLAlignedTgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<bdm::SharedData<bdm::MathArray<double,3> >::AlignedT>) );
      instance.SetNew(&new_vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO3gRsPgRcLcLAlignedTgR);
      instance.SetNewArray(&newArray_vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO3gRsPgRcLcLAlignedTgR);
      instance.SetDelete(&delete_vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO3gRsPgRcLcLAlignedTgR);
      instance.SetDeleteArray(&deleteArray_vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO3gRsPgRcLcLAlignedTgR);
      instance.SetDestructor(&destruct_vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO3gRsPgRcLcLAlignedTgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<bdm::SharedData<bdm::MathArray<double,3> >::AlignedT> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<bdm::SharedData<bdm::MathArray<double,3> >::AlignedT>","std::__1::vector<bdm::SharedData<bdm::MathArray<double, 3ul>>::AlignedT, std::__1::allocator<bdm::SharedData<bdm::MathArray<double, 3ul>>::AlignedT>>"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<bdm::SharedData<bdm::MathArray<double,3> >::AlignedT>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO3gRsPgRcLcLAlignedTgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<bdm::SharedData<bdm::MathArray<double,3> >::AlignedT>*>(nullptr))->GetClass();
      vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO3gRsPgRcLcLAlignedTgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO3gRsPgRcLcLAlignedTgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO3gRsPgRcLcLAlignedTgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<bdm::SharedData<bdm::MathArray<double,3> >::AlignedT> : new vector<bdm::SharedData<bdm::MathArray<double,3> >::AlignedT>;
   }
   static void *newArray_vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO3gRsPgRcLcLAlignedTgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<bdm::SharedData<bdm::MathArray<double,3> >::AlignedT>[nElements] : new vector<bdm::SharedData<bdm::MathArray<double,3> >::AlignedT>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO3gRsPgRcLcLAlignedTgR(void *p) {
      delete (static_cast<vector<bdm::SharedData<bdm::MathArray<double,3> >::AlignedT>*>(p));
   }
   static void deleteArray_vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO3gRsPgRcLcLAlignedTgR(void *p) {
      delete [] (static_cast<vector<bdm::SharedData<bdm::MathArray<double,3> >::AlignedT>*>(p));
   }
   static void destruct_vectorlEbdmcLcLSharedDatalEbdmcLcLMathArraylEdoublecO3gRsPgRcLcLAlignedTgR(void *p) {
      typedef vector<bdm::SharedData<bdm::MathArray<double,3> >::AlignedT> current_t;
      (static_cast<current_t*>(p))->~current_t();
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
         instance("vector<bdm::SharedData<ULong64_t>::AlignedT>", -2, "vector", 493,
                  typeid(vector<bdm::SharedData<ULong64_t>::AlignedT>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEbdmcLcLSharedDatalEULong64_tgRcLcLAlignedTgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<bdm::SharedData<ULong64_t>::AlignedT>) );
      instance.SetNew(&new_vectorlEbdmcLcLSharedDatalEULong64_tgRcLcLAlignedTgR);
      instance.SetNewArray(&newArray_vectorlEbdmcLcLSharedDatalEULong64_tgRcLcLAlignedTgR);
      instance.SetDelete(&delete_vectorlEbdmcLcLSharedDatalEULong64_tgRcLcLAlignedTgR);
      instance.SetDeleteArray(&deleteArray_vectorlEbdmcLcLSharedDatalEULong64_tgRcLcLAlignedTgR);
      instance.SetDestructor(&destruct_vectorlEbdmcLcLSharedDatalEULong64_tgRcLcLAlignedTgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<bdm::SharedData<ULong64_t>::AlignedT> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<bdm::SharedData<ULong64_t>::AlignedT>","std::__1::vector<bdm::SharedData<unsigned long long>::AlignedT, std::__1::allocator<bdm::SharedData<unsigned long long>::AlignedT>>"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<bdm::SharedData<ULong64_t>::AlignedT>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEbdmcLcLSharedDatalEULong64_tgRcLcLAlignedTgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<bdm::SharedData<ULong64_t>::AlignedT>*>(nullptr))->GetClass();
      vectorlEbdmcLcLSharedDatalEULong64_tgRcLcLAlignedTgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEbdmcLcLSharedDatalEULong64_tgRcLcLAlignedTgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEbdmcLcLSharedDatalEULong64_tgRcLcLAlignedTgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<bdm::SharedData<ULong64_t>::AlignedT> : new vector<bdm::SharedData<ULong64_t>::AlignedT>;
   }
   static void *newArray_vectorlEbdmcLcLSharedDatalEULong64_tgRcLcLAlignedTgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<bdm::SharedData<ULong64_t>::AlignedT>[nElements] : new vector<bdm::SharedData<ULong64_t>::AlignedT>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEbdmcLcLSharedDatalEULong64_tgRcLcLAlignedTgR(void *p) {
      delete (static_cast<vector<bdm::SharedData<ULong64_t>::AlignedT>*>(p));
   }
   static void deleteArray_vectorlEbdmcLcLSharedDatalEULong64_tgRcLcLAlignedTgR(void *p) {
      delete [] (static_cast<vector<bdm::SharedData<ULong64_t>::AlignedT>*>(p));
   }
   static void destruct_vectorlEbdmcLcLSharedDatalEULong64_tgRcLcLAlignedTgR(void *p) {
      typedef vector<bdm::SharedData<ULong64_t>::AlignedT> current_t;
      (static_cast<current_t*>(p))->~current_t();
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
         instance("vector<bdm::Random*>", -2, "vector", 493,
                  typeid(vector<bdm::Random*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEbdmcLcLRandommUgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<bdm::Random*>) );
      instance.SetNew(&new_vectorlEbdmcLcLRandommUgR);
      instance.SetNewArray(&newArray_vectorlEbdmcLcLRandommUgR);
      instance.SetDelete(&delete_vectorlEbdmcLcLRandommUgR);
      instance.SetDeleteArray(&deleteArray_vectorlEbdmcLcLRandommUgR);
      instance.SetDestructor(&destruct_vectorlEbdmcLcLRandommUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<bdm::Random*> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<bdm::Random*>","std::__1::vector<bdm::Random*, std::__1::allocator<bdm::Random*>>"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<bdm::Random*>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEbdmcLcLRandommUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<bdm::Random*>*>(nullptr))->GetClass();
      vectorlEbdmcLcLRandommUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEbdmcLcLRandommUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEbdmcLcLRandommUgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<bdm::Random*> : new vector<bdm::Random*>;
   }
   static void *newArray_vectorlEbdmcLcLRandommUgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<bdm::Random*>[nElements] : new vector<bdm::Random*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEbdmcLcLRandommUgR(void *p) {
      delete (static_cast<vector<bdm::Random*>*>(p));
   }
   static void deleteArray_vectorlEbdmcLcLRandommUgR(void *p) {
      delete [] (static_cast<vector<bdm::Random*>*>(p));
   }
   static void destruct_vectorlEbdmcLcLRandommUgR(void *p) {
      typedef vector<bdm::Random*> current_t;
      (static_cast<current_t*>(p))->~current_t();
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
         instance("vector<bdm::Param::VisualizeDiffusion>", -2, "vector", 493,
                  typeid(vector<bdm::Param::VisualizeDiffusion>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEbdmcLcLParamcLcLVisualizeDiffusiongR_Dictionary, isa_proxy, 4,
                  sizeof(vector<bdm::Param::VisualizeDiffusion>) );
      instance.SetNew(&new_vectorlEbdmcLcLParamcLcLVisualizeDiffusiongR);
      instance.SetNewArray(&newArray_vectorlEbdmcLcLParamcLcLVisualizeDiffusiongR);
      instance.SetDelete(&delete_vectorlEbdmcLcLParamcLcLVisualizeDiffusiongR);
      instance.SetDeleteArray(&deleteArray_vectorlEbdmcLcLParamcLcLVisualizeDiffusiongR);
      instance.SetDestructor(&destruct_vectorlEbdmcLcLParamcLcLVisualizeDiffusiongR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<bdm::Param::VisualizeDiffusion> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<bdm::Param::VisualizeDiffusion>","std::__1::vector<bdm::Param::VisualizeDiffusion, std::__1::allocator<bdm::Param::VisualizeDiffusion>>"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<bdm::Param::VisualizeDiffusion>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEbdmcLcLParamcLcLVisualizeDiffusiongR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<bdm::Param::VisualizeDiffusion>*>(nullptr))->GetClass();
      vectorlEbdmcLcLParamcLcLVisualizeDiffusiongR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEbdmcLcLParamcLcLVisualizeDiffusiongR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEbdmcLcLParamcLcLVisualizeDiffusiongR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<bdm::Param::VisualizeDiffusion> : new vector<bdm::Param::VisualizeDiffusion>;
   }
   static void *newArray_vectorlEbdmcLcLParamcLcLVisualizeDiffusiongR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<bdm::Param::VisualizeDiffusion>[nElements] : new vector<bdm::Param::VisualizeDiffusion>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEbdmcLcLParamcLcLVisualizeDiffusiongR(void *p) {
      delete (static_cast<vector<bdm::Param::VisualizeDiffusion>*>(p));
   }
   static void deleteArray_vectorlEbdmcLcLParamcLcLVisualizeDiffusiongR(void *p) {
      delete [] (static_cast<vector<bdm::Param::VisualizeDiffusion>*>(p));
   }
   static void destruct_vectorlEbdmcLcLParamcLcLVisualizeDiffusiongR(void *p) {
      typedef vector<bdm::Param::VisualizeDiffusion> current_t;
      (static_cast<current_t*>(p))->~current_t();
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
         instance("vector<bdm::OperationImpl*>", -2, "vector", 493,
                  typeid(vector<bdm::OperationImpl*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEbdmcLcLOperationImplmUgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<bdm::OperationImpl*>) );
      instance.SetNew(&new_vectorlEbdmcLcLOperationImplmUgR);
      instance.SetNewArray(&newArray_vectorlEbdmcLcLOperationImplmUgR);
      instance.SetDelete(&delete_vectorlEbdmcLcLOperationImplmUgR);
      instance.SetDeleteArray(&deleteArray_vectorlEbdmcLcLOperationImplmUgR);
      instance.SetDestructor(&destruct_vectorlEbdmcLcLOperationImplmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<bdm::OperationImpl*> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<bdm::OperationImpl*>","std::__1::vector<bdm::OperationImpl*, std::__1::allocator<bdm::OperationImpl*>>"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<bdm::OperationImpl*>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEbdmcLcLOperationImplmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<bdm::OperationImpl*>*>(nullptr))->GetClass();
      vectorlEbdmcLcLOperationImplmUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEbdmcLcLOperationImplmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEbdmcLcLOperationImplmUgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<bdm::OperationImpl*> : new vector<bdm::OperationImpl*>;
   }
   static void *newArray_vectorlEbdmcLcLOperationImplmUgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<bdm::OperationImpl*>[nElements] : new vector<bdm::OperationImpl*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEbdmcLcLOperationImplmUgR(void *p) {
      delete (static_cast<vector<bdm::OperationImpl*>*>(p));
   }
   static void deleteArray_vectorlEbdmcLcLOperationImplmUgR(void *p) {
      delete [] (static_cast<vector<bdm::OperationImpl*>*>(p));
   }
   static void destruct_vectorlEbdmcLcLOperationImplmUgR(void *p) {
      typedef vector<bdm::OperationImpl*> current_t;
      (static_cast<current_t*>(p))->~current_t();
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
         instance("vector<bdm::Operation*>", -2, "vector", 493,
                  typeid(vector<bdm::Operation*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEbdmcLcLOperationmUgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<bdm::Operation*>) );
      instance.SetNew(&new_vectorlEbdmcLcLOperationmUgR);
      instance.SetNewArray(&newArray_vectorlEbdmcLcLOperationmUgR);
      instance.SetDelete(&delete_vectorlEbdmcLcLOperationmUgR);
      instance.SetDeleteArray(&deleteArray_vectorlEbdmcLcLOperationmUgR);
      instance.SetDestructor(&destruct_vectorlEbdmcLcLOperationmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<bdm::Operation*> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<bdm::Operation*>","std::__1::vector<bdm::Operation*, std::__1::allocator<bdm::Operation*>>"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<bdm::Operation*>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEbdmcLcLOperationmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<bdm::Operation*>*>(nullptr))->GetClass();
      vectorlEbdmcLcLOperationmUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEbdmcLcLOperationmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEbdmcLcLOperationmUgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<bdm::Operation*> : new vector<bdm::Operation*>;
   }
   static void *newArray_vectorlEbdmcLcLOperationmUgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<bdm::Operation*>[nElements] : new vector<bdm::Operation*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEbdmcLcLOperationmUgR(void *p) {
      delete (static_cast<vector<bdm::Operation*>*>(p));
   }
   static void deleteArray_vectorlEbdmcLcLOperationmUgR(void *p) {
      delete [] (static_cast<vector<bdm::Operation*>*>(p));
   }
   static void destruct_vectorlEbdmcLcLOperationmUgR(void *p) {
      typedef vector<bdm::Operation*> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<bdm::Operation*>

namespace ROOT {
   static TClass *vectorlEbdmcLcLMathArraylEdoublecO3gRsPgR_Dictionary();
   static void vectorlEbdmcLcLMathArraylEdoublecO3gRsPgR_TClassManip(TClass*);
   static void *new_vectorlEbdmcLcLMathArraylEdoublecO3gRsPgR(void *p = nullptr);
   static void *newArray_vectorlEbdmcLcLMathArraylEdoublecO3gRsPgR(Long_t size, void *p);
   static void delete_vectorlEbdmcLcLMathArraylEdoublecO3gRsPgR(void *p);
   static void deleteArray_vectorlEbdmcLcLMathArraylEdoublecO3gRsPgR(void *p);
   static void destruct_vectorlEbdmcLcLMathArraylEdoublecO3gRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<bdm::MathArray<double,3> >*)
   {
      vector<bdm::MathArray<double,3> > *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<bdm::MathArray<double,3> >));
      static ::ROOT::TGenericClassInfo 
         instance("vector<bdm::MathArray<double,3> >", -2, "vector", 493,
                  typeid(vector<bdm::MathArray<double,3> >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEbdmcLcLMathArraylEdoublecO3gRsPgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<bdm::MathArray<double,3> >) );
      instance.SetNew(&new_vectorlEbdmcLcLMathArraylEdoublecO3gRsPgR);
      instance.SetNewArray(&newArray_vectorlEbdmcLcLMathArraylEdoublecO3gRsPgR);
      instance.SetDelete(&delete_vectorlEbdmcLcLMathArraylEdoublecO3gRsPgR);
      instance.SetDeleteArray(&deleteArray_vectorlEbdmcLcLMathArraylEdoublecO3gRsPgR);
      instance.SetDestructor(&destruct_vectorlEbdmcLcLMathArraylEdoublecO3gRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<bdm::MathArray<double,3> > >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<bdm::MathArray<double,3> >","std::__1::vector<bdm::MathArray<double, 3ul>, std::__1::allocator<bdm::MathArray<double, 3ul>>>"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<bdm::MathArray<double,3> >*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEbdmcLcLMathArraylEdoublecO3gRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<bdm::MathArray<double,3> >*>(nullptr))->GetClass();
      vectorlEbdmcLcLMathArraylEdoublecO3gRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEbdmcLcLMathArraylEdoublecO3gRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEbdmcLcLMathArraylEdoublecO3gRsPgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<bdm::MathArray<double,3> > : new vector<bdm::MathArray<double,3> >;
   }
   static void *newArray_vectorlEbdmcLcLMathArraylEdoublecO3gRsPgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<bdm::MathArray<double,3> >[nElements] : new vector<bdm::MathArray<double,3> >[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEbdmcLcLMathArraylEdoublecO3gRsPgR(void *p) {
      delete (static_cast<vector<bdm::MathArray<double,3> >*>(p));
   }
   static void deleteArray_vectorlEbdmcLcLMathArraylEdoublecO3gRsPgR(void *p) {
      delete [] (static_cast<vector<bdm::MathArray<double,3> >*>(p));
   }
   static void destruct_vectorlEbdmcLcLMathArraylEdoublecO3gRsPgR(void *p) {
      typedef vector<bdm::MathArray<double,3> > current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<bdm::MathArray<double,3> >

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
         instance("vector<bdm::Functor<bool,bdm::Agent*>*>", -2, "vector", 493,
                  typeid(vector<bdm::Functor<bool,bdm::Agent*>*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEbdmcLcLFunctorlEboolcObdmcLcLAgentmUgRmUgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<bdm::Functor<bool,bdm::Agent*>*>) );
      instance.SetNew(&new_vectorlEbdmcLcLFunctorlEboolcObdmcLcLAgentmUgRmUgR);
      instance.SetNewArray(&newArray_vectorlEbdmcLcLFunctorlEboolcObdmcLcLAgentmUgRmUgR);
      instance.SetDelete(&delete_vectorlEbdmcLcLFunctorlEboolcObdmcLcLAgentmUgRmUgR);
      instance.SetDeleteArray(&deleteArray_vectorlEbdmcLcLFunctorlEboolcObdmcLcLAgentmUgRmUgR);
      instance.SetDestructor(&destruct_vectorlEbdmcLcLFunctorlEboolcObdmcLcLAgentmUgRmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<bdm::Functor<bool,bdm::Agent*>*> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<bdm::Functor<bool,bdm::Agent*>*>","std::__1::vector<bdm::Functor<bool, bdm::Agent*>*, std::__1::allocator<bdm::Functor<bool, bdm::Agent*>*>>"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<bdm::Functor<bool,bdm::Agent*>*>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEbdmcLcLFunctorlEboolcObdmcLcLAgentmUgRmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<bdm::Functor<bool,bdm::Agent*>*>*>(nullptr))->GetClass();
      vectorlEbdmcLcLFunctorlEboolcObdmcLcLAgentmUgRmUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEbdmcLcLFunctorlEboolcObdmcLcLAgentmUgRmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEbdmcLcLFunctorlEboolcObdmcLcLAgentmUgRmUgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<bdm::Functor<bool,bdm::Agent*>*> : new vector<bdm::Functor<bool,bdm::Agent*>*>;
   }
   static void *newArray_vectorlEbdmcLcLFunctorlEboolcObdmcLcLAgentmUgRmUgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<bdm::Functor<bool,bdm::Agent*>*>[nElements] : new vector<bdm::Functor<bool,bdm::Agent*>*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEbdmcLcLFunctorlEboolcObdmcLcLAgentmUgRmUgR(void *p) {
      delete (static_cast<vector<bdm::Functor<bool,bdm::Agent*>*>*>(p));
   }
   static void deleteArray_vectorlEbdmcLcLFunctorlEboolcObdmcLcLAgentmUgRmUgR(void *p) {
      delete [] (static_cast<vector<bdm::Functor<bool,bdm::Agent*>*>*>(p));
   }
   static void destruct_vectorlEbdmcLcLFunctorlEboolcObdmcLcLAgentmUgRmUgR(void *p) {
      typedef vector<bdm::Functor<bool,bdm::Agent*>*> current_t;
      (static_cast<current_t*>(p))->~current_t();
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
         instance("vector<bdm::ExecutionContext*>", -2, "vector", 493,
                  typeid(vector<bdm::ExecutionContext*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEbdmcLcLExecutionContextmUgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<bdm::ExecutionContext*>) );
      instance.SetNew(&new_vectorlEbdmcLcLExecutionContextmUgR);
      instance.SetNewArray(&newArray_vectorlEbdmcLcLExecutionContextmUgR);
      instance.SetDelete(&delete_vectorlEbdmcLcLExecutionContextmUgR);
      instance.SetDeleteArray(&deleteArray_vectorlEbdmcLcLExecutionContextmUgR);
      instance.SetDestructor(&destruct_vectorlEbdmcLcLExecutionContextmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<bdm::ExecutionContext*> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<bdm::ExecutionContext*>","std::__1::vector<bdm::ExecutionContext*, std::__1::allocator<bdm::ExecutionContext*>>"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<bdm::ExecutionContext*>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEbdmcLcLExecutionContextmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<bdm::ExecutionContext*>*>(nullptr))->GetClass();
      vectorlEbdmcLcLExecutionContextmUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEbdmcLcLExecutionContextmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEbdmcLcLExecutionContextmUgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<bdm::ExecutionContext*> : new vector<bdm::ExecutionContext*>;
   }
   static void *newArray_vectorlEbdmcLcLExecutionContextmUgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<bdm::ExecutionContext*>[nElements] : new vector<bdm::ExecutionContext*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEbdmcLcLExecutionContextmUgR(void *p) {
      delete (static_cast<vector<bdm::ExecutionContext*>*>(p));
   }
   static void deleteArray_vectorlEbdmcLcLExecutionContextmUgR(void *p) {
      delete [] (static_cast<vector<bdm::ExecutionContext*>*>(p));
   }
   static void destruct_vectorlEbdmcLcLExecutionContextmUgR(void *p) {
      typedef vector<bdm::ExecutionContext*> current_t;
      (static_cast<current_t*>(p))->~current_t();
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
         instance("vector<bdm::Behavior*>", -2, "vector", 493,
                  typeid(vector<bdm::Behavior*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEbdmcLcLBehaviormUgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<bdm::Behavior*>) );
      instance.SetNew(&new_vectorlEbdmcLcLBehaviormUgR);
      instance.SetNewArray(&newArray_vectorlEbdmcLcLBehaviormUgR);
      instance.SetDelete(&delete_vectorlEbdmcLcLBehaviormUgR);
      instance.SetDeleteArray(&deleteArray_vectorlEbdmcLcLBehaviormUgR);
      instance.SetDestructor(&destruct_vectorlEbdmcLcLBehaviormUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<bdm::Behavior*> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<bdm::Behavior*>","std::__1::vector<bdm::Behavior*, std::__1::allocator<bdm::Behavior*>>"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<bdm::Behavior*>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEbdmcLcLBehaviormUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<bdm::Behavior*>*>(nullptr))->GetClass();
      vectorlEbdmcLcLBehaviormUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEbdmcLcLBehaviormUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEbdmcLcLBehaviormUgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<bdm::Behavior*> : new vector<bdm::Behavior*>;
   }
   static void *newArray_vectorlEbdmcLcLBehaviormUgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<bdm::Behavior*>[nElements] : new vector<bdm::Behavior*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEbdmcLcLBehaviormUgR(void *p) {
      delete (static_cast<vector<bdm::Behavior*>*>(p));
   }
   static void deleteArray_vectorlEbdmcLcLBehaviormUgR(void *p) {
      delete [] (static_cast<vector<bdm::Behavior*>*>(p));
   }
   static void destruct_vectorlEbdmcLcLBehaviormUgR(void *p) {
      typedef vector<bdm::Behavior*> current_t;
      (static_cast<current_t*>(p))->~current_t();
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
         instance("vector<bdm::AgentUid>", -2, "vector", 493,
                  typeid(vector<bdm::AgentUid>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEbdmcLcLAgentUidgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<bdm::AgentUid>) );
      instance.SetNew(&new_vectorlEbdmcLcLAgentUidgR);
      instance.SetNewArray(&newArray_vectorlEbdmcLcLAgentUidgR);
      instance.SetDelete(&delete_vectorlEbdmcLcLAgentUidgR);
      instance.SetDeleteArray(&deleteArray_vectorlEbdmcLcLAgentUidgR);
      instance.SetDestructor(&destruct_vectorlEbdmcLcLAgentUidgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<bdm::AgentUid> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<bdm::AgentUid>","std::__1::vector<bdm::AgentUid, std::__1::allocator<bdm::AgentUid>>"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<bdm::AgentUid>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEbdmcLcLAgentUidgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<bdm::AgentUid>*>(nullptr))->GetClass();
      vectorlEbdmcLcLAgentUidgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEbdmcLcLAgentUidgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEbdmcLcLAgentUidgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<bdm::AgentUid> : new vector<bdm::AgentUid>;
   }
   static void *newArray_vectorlEbdmcLcLAgentUidgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<bdm::AgentUid>[nElements] : new vector<bdm::AgentUid>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEbdmcLcLAgentUidgR(void *p) {
      delete (static_cast<vector<bdm::AgentUid>*>(p));
   }
   static void deleteArray_vectorlEbdmcLcLAgentUidgR(void *p) {
      delete [] (static_cast<vector<bdm::AgentUid>*>(p));
   }
   static void destruct_vectorlEbdmcLcLAgentUidgR(void *p) {
      typedef vector<bdm::AgentUid> current_t;
      (static_cast<current_t*>(p))->~current_t();
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
         instance("vector<bdm::AgentPointer<bdm::neuroscience::NeuriteElement> >", -2, "vector", 493,
                  typeid(vector<bdm::AgentPointer<bdm::neuroscience::NeuriteElement> >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEbdmcLcLAgentPointerlEbdmcLcLneurosciencecLcLNeuriteElementgRsPgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<bdm::AgentPointer<bdm::neuroscience::NeuriteElement> >) );
      instance.SetNew(&new_vectorlEbdmcLcLAgentPointerlEbdmcLcLneurosciencecLcLNeuriteElementgRsPgR);
      instance.SetNewArray(&newArray_vectorlEbdmcLcLAgentPointerlEbdmcLcLneurosciencecLcLNeuriteElementgRsPgR);
      instance.SetDelete(&delete_vectorlEbdmcLcLAgentPointerlEbdmcLcLneurosciencecLcLNeuriteElementgRsPgR);
      instance.SetDeleteArray(&deleteArray_vectorlEbdmcLcLAgentPointerlEbdmcLcLneurosciencecLcLNeuriteElementgRsPgR);
      instance.SetDestructor(&destruct_vectorlEbdmcLcLAgentPointerlEbdmcLcLneurosciencecLcLNeuriteElementgRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<bdm::AgentPointer<bdm::neuroscience::NeuriteElement> > >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<bdm::AgentPointer<bdm::neuroscience::NeuriteElement> >","std::__1::vector<bdm::AgentPointer<bdm::neuroscience::NeuriteElement>, std::__1::allocator<bdm::AgentPointer<bdm::neuroscience::NeuriteElement>>>"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<bdm::AgentPointer<bdm::neuroscience::NeuriteElement> >*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEbdmcLcLAgentPointerlEbdmcLcLneurosciencecLcLNeuriteElementgRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<bdm::AgentPointer<bdm::neuroscience::NeuriteElement> >*>(nullptr))->GetClass();
      vectorlEbdmcLcLAgentPointerlEbdmcLcLneurosciencecLcLNeuriteElementgRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEbdmcLcLAgentPointerlEbdmcLcLneurosciencecLcLNeuriteElementgRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEbdmcLcLAgentPointerlEbdmcLcLneurosciencecLcLNeuriteElementgRsPgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<bdm::AgentPointer<bdm::neuroscience::NeuriteElement> > : new vector<bdm::AgentPointer<bdm::neuroscience::NeuriteElement> >;
   }
   static void *newArray_vectorlEbdmcLcLAgentPointerlEbdmcLcLneurosciencecLcLNeuriteElementgRsPgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<bdm::AgentPointer<bdm::neuroscience::NeuriteElement> >[nElements] : new vector<bdm::AgentPointer<bdm::neuroscience::NeuriteElement> >[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEbdmcLcLAgentPointerlEbdmcLcLneurosciencecLcLNeuriteElementgRsPgR(void *p) {
      delete (static_cast<vector<bdm::AgentPointer<bdm::neuroscience::NeuriteElement> >*>(p));
   }
   static void deleteArray_vectorlEbdmcLcLAgentPointerlEbdmcLcLneurosciencecLcLNeuriteElementgRsPgR(void *p) {
      delete [] (static_cast<vector<bdm::AgentPointer<bdm::neuroscience::NeuriteElement> >*>(p));
   }
   static void destruct_vectorlEbdmcLcLAgentPointerlEbdmcLcLneurosciencecLcLNeuriteElementgRsPgR(void *p) {
      typedef vector<bdm::AgentPointer<bdm::neuroscience::NeuriteElement> > current_t;
      (static_cast<current_t*>(p))->~current_t();
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
         instance("vector<bdm::AgentPointer<bdm::Agent> >", -2, "vector", 493,
                  typeid(vector<bdm::AgentPointer<bdm::Agent> >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEbdmcLcLAgentPointerlEbdmcLcLAgentgRsPgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<bdm::AgentPointer<bdm::Agent> >) );
      instance.SetNew(&new_vectorlEbdmcLcLAgentPointerlEbdmcLcLAgentgRsPgR);
      instance.SetNewArray(&newArray_vectorlEbdmcLcLAgentPointerlEbdmcLcLAgentgRsPgR);
      instance.SetDelete(&delete_vectorlEbdmcLcLAgentPointerlEbdmcLcLAgentgRsPgR);
      instance.SetDeleteArray(&deleteArray_vectorlEbdmcLcLAgentPointerlEbdmcLcLAgentgRsPgR);
      instance.SetDestructor(&destruct_vectorlEbdmcLcLAgentPointerlEbdmcLcLAgentgRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<bdm::AgentPointer<bdm::Agent> > >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<bdm::AgentPointer<bdm::Agent> >","std::__1::vector<bdm::AgentPointer<bdm::Agent>, std::__1::allocator<bdm::AgentPointer<bdm::Agent>>>"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<bdm::AgentPointer<bdm::Agent> >*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEbdmcLcLAgentPointerlEbdmcLcLAgentgRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<bdm::AgentPointer<bdm::Agent> >*>(nullptr))->GetClass();
      vectorlEbdmcLcLAgentPointerlEbdmcLcLAgentgRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEbdmcLcLAgentPointerlEbdmcLcLAgentgRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEbdmcLcLAgentPointerlEbdmcLcLAgentgRsPgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<bdm::AgentPointer<bdm::Agent> > : new vector<bdm::AgentPointer<bdm::Agent> >;
   }
   static void *newArray_vectorlEbdmcLcLAgentPointerlEbdmcLcLAgentgRsPgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<bdm::AgentPointer<bdm::Agent> >[nElements] : new vector<bdm::AgentPointer<bdm::Agent> >[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEbdmcLcLAgentPointerlEbdmcLcLAgentgRsPgR(void *p) {
      delete (static_cast<vector<bdm::AgentPointer<bdm::Agent> >*>(p));
   }
   static void deleteArray_vectorlEbdmcLcLAgentPointerlEbdmcLcLAgentgRsPgR(void *p) {
      delete [] (static_cast<vector<bdm::AgentPointer<bdm::Agent> >*>(p));
   }
   static void destruct_vectorlEbdmcLcLAgentPointerlEbdmcLcLAgentgRsPgR(void *p) {
      typedef vector<bdm::AgentPointer<bdm::Agent> > current_t;
      (static_cast<current_t*>(p))->~current_t();
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
         instance("vector<bdm::AgentHandle>", -2, "vector", 493,
                  typeid(vector<bdm::AgentHandle>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEbdmcLcLAgentHandlegR_Dictionary, isa_proxy, 4,
                  sizeof(vector<bdm::AgentHandle>) );
      instance.SetNew(&new_vectorlEbdmcLcLAgentHandlegR);
      instance.SetNewArray(&newArray_vectorlEbdmcLcLAgentHandlegR);
      instance.SetDelete(&delete_vectorlEbdmcLcLAgentHandlegR);
      instance.SetDeleteArray(&deleteArray_vectorlEbdmcLcLAgentHandlegR);
      instance.SetDestructor(&destruct_vectorlEbdmcLcLAgentHandlegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<bdm::AgentHandle> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<bdm::AgentHandle>","std::__1::vector<bdm::AgentHandle, std::__1::allocator<bdm::AgentHandle>>"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<bdm::AgentHandle>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEbdmcLcLAgentHandlegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<bdm::AgentHandle>*>(nullptr))->GetClass();
      vectorlEbdmcLcLAgentHandlegR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEbdmcLcLAgentHandlegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEbdmcLcLAgentHandlegR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<bdm::AgentHandle> : new vector<bdm::AgentHandle>;
   }
   static void *newArray_vectorlEbdmcLcLAgentHandlegR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<bdm::AgentHandle>[nElements] : new vector<bdm::AgentHandle>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEbdmcLcLAgentHandlegR(void *p) {
      delete (static_cast<vector<bdm::AgentHandle>*>(p));
   }
   static void deleteArray_vectorlEbdmcLcLAgentHandlegR(void *p) {
      delete [] (static_cast<vector<bdm::AgentHandle>*>(p));
   }
   static void destruct_vectorlEbdmcLcLAgentHandlegR(void *p) {
      typedef vector<bdm::AgentHandle> current_t;
      (static_cast<current_t*>(p))->~current_t();
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
         instance("vector<bdm::Agent*>", -2, "vector", 493,
                  typeid(vector<bdm::Agent*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEbdmcLcLAgentmUgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<bdm::Agent*>) );
      instance.SetNew(&new_vectorlEbdmcLcLAgentmUgR);
      instance.SetNewArray(&newArray_vectorlEbdmcLcLAgentmUgR);
      instance.SetDelete(&delete_vectorlEbdmcLcLAgentmUgR);
      instance.SetDeleteArray(&deleteArray_vectorlEbdmcLcLAgentmUgR);
      instance.SetDestructor(&destruct_vectorlEbdmcLcLAgentmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<bdm::Agent*> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<bdm::Agent*>","std::__1::vector<bdm::Agent*, std::__1::allocator<bdm::Agent*>>"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<bdm::Agent*>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEbdmcLcLAgentmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<bdm::Agent*>*>(nullptr))->GetClass();
      vectorlEbdmcLcLAgentmUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEbdmcLcLAgentmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEbdmcLcLAgentmUgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<bdm::Agent*> : new vector<bdm::Agent*>;
   }
   static void *newArray_vectorlEbdmcLcLAgentmUgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<bdm::Agent*>[nElements] : new vector<bdm::Agent*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEbdmcLcLAgentmUgR(void *p) {
      delete (static_cast<vector<bdm::Agent*>*>(p));
   }
   static void deleteArray_vectorlEbdmcLcLAgentmUgR(void *p) {
      delete [] (static_cast<vector<bdm::Agent*>*>(p));
   }
   static void destruct_vectorlEbdmcLcLAgentmUgR(void *p) {
      typedef vector<bdm::Agent*> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<bdm::Agent*>

namespace ROOT {
   static TClass *vectorlEarraylEdoublecO8gRsPgR_Dictionary();
   static void vectorlEarraylEdoublecO8gRsPgR_TClassManip(TClass*);
   static void *new_vectorlEarraylEdoublecO8gRsPgR(void *p = nullptr);
   static void *newArray_vectorlEarraylEdoublecO8gRsPgR(Long_t size, void *p);
   static void delete_vectorlEarraylEdoublecO8gRsPgR(void *p);
   static void deleteArray_vectorlEarraylEdoublecO8gRsPgR(void *p);
   static void destruct_vectorlEarraylEdoublecO8gRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<array<double,8> >*)
   {
      vector<array<double,8> > *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<array<double,8> >));
      static ::ROOT::TGenericClassInfo 
         instance("vector<array<double,8> >", -2, "vector", 493,
                  typeid(vector<array<double,8> >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEarraylEdoublecO8gRsPgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<array<double,8> >) );
      instance.SetNew(&new_vectorlEarraylEdoublecO8gRsPgR);
      instance.SetNewArray(&newArray_vectorlEarraylEdoublecO8gRsPgR);
      instance.SetDelete(&delete_vectorlEarraylEdoublecO8gRsPgR);
      instance.SetDeleteArray(&deleteArray_vectorlEarraylEdoublecO8gRsPgR);
      instance.SetDestructor(&destruct_vectorlEarraylEdoublecO8gRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<array<double,8> > >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<array<double,8> >","std::__1::vector<std::__1::array<double, 8ul>, std::__1::allocator<std::__1::array<double, 8ul>>>"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<array<double,8> >*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEarraylEdoublecO8gRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<array<double,8> >*>(nullptr))->GetClass();
      vectorlEarraylEdoublecO8gRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEarraylEdoublecO8gRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEarraylEdoublecO8gRsPgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<array<double,8> > : new vector<array<double,8> >;
   }
   static void *newArray_vectorlEarraylEdoublecO8gRsPgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<array<double,8> >[nElements] : new vector<array<double,8> >[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEarraylEdoublecO8gRsPgR(void *p) {
      delete (static_cast<vector<array<double,8> >*>(p));
   }
   static void deleteArray_vectorlEarraylEdoublecO8gRsPgR(void *p) {
      delete [] (static_cast<vector<array<double,8> >*>(p));
   }
   static void destruct_vectorlEarraylEdoublecO8gRsPgR(void *p) {
      typedef vector<array<double,8> > current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<array<double,8> >

namespace {
  void TriggerDictionaryInitialization_libunitmItestmImechanicsmItwomIcells_dict_Impl() {
    static const char* headers[] = {
"0",
nullptr
    };
    static const char* includePaths[] = {
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "libunitmItestmImechanicsmItwomIcells_dict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
namespace bdm{struct __attribute__((annotate("$clingAutoload$core/operation/operation.h")))  __attribute__((annotate("$clingAutoload$core/behavior/behavior.h")))  OperationImpl;}
namespace std{inline namespace __1{template <class _Tp> class __attribute__((annotate("$clingAutoload$iosfwd")))  __attribute__((annotate("$clingAutoload$string")))  allocator;
}}
namespace bdm{class __attribute__((annotate("$clingAutoload$core/execution_context/execution_context.h")))  __attribute__((annotate("$clingAutoload$core/behavior/behavior.h")))  ExecutionContext;}
namespace bdm{struct __attribute__((annotate("$clingAutoload$core/operation/operation.h")))  __attribute__((annotate("$clingAutoload$core/behavior/behavior.h")))  Operation;}
namespace bdm{class __attribute__((annotate("$clingAutoload$core/util/random.h")))  __attribute__((annotate("$clingAutoload$core/behavior/behavior.h")))  Random;}
namespace bdm{class __attribute__((annotate("$clingAutoload$core/agent/agent.h")))  __attribute__((annotate("$clingAutoload$core/behavior/behavior.h")))  Agent;}
namespace bdm{class __attribute__((annotate("$clingAutoload$core/behavior/behavior.h")))  Behavior;}
namespace bdm{template <typename TAgent = bdm::Agent> class __attribute__((annotate("$clingAutoload$core/agent/agent_pointer.h")))  __attribute__((annotate("$clingAutoload$core/behavior/behavior.h")))  AgentPointer;
}
namespace bdm{class __attribute__((annotate("$clingAutoload$core/agent/agent_uid.h")))  __attribute__((annotate("$clingAutoload$core/behavior/behavior.h")))  AgentUid;}
namespace bdm{class __attribute__((annotate("$clingAutoload$core/util/spinlock.h")))  __attribute__((annotate("$clingAutoload$core/behavior/behavior.h")))  Spinlock;}
namespace bdm{template <typename TReturn, typename ...TArgs> class __attribute__((annotate("$clingAutoload$core/functor.h")))  __attribute__((annotate("$clingAutoload$core/behavior/behavior.h")))  Functor;
}
namespace bdm{class __attribute__((annotate("$clingAutoload$core/agent/agent_handle.h")))  __attribute__((annotate("$clingAutoload$core/behavior/behavior.h")))  AgentHandle;}
namespace bdm{namespace neuroscience{class __attribute__((annotate("$clingAutoload$neuroscience/neurite_element.h")))  __attribute__((annotate("$clingAutoload$biodynamo.h")))  NeuriteElement;}}
namespace bdm{template <typename T> class __attribute__((annotate("$clingAutoload$core/util/iterator.h")))  __attribute__((annotate("$clingAutoload$biodynamo.h")))  Iterator;
}
namespace bdm{template <typename T> class __attribute__((annotate("$clingAutoload$core/container/shared_data.h")))  __attribute__((annotate("$clingAutoload$biodynamo.h")))  SharedData;
}
namespace bdm{class __attribute__((annotate("$clingAutoload$core/util/progress_bar.h")))  __attribute__((annotate("$clingAutoload$biodynamo.h")))  ProgressBar;}
namespace bdm{class __attribute__((annotate("$clingAutoload$core/diffusion/continuum_interface.h")))  __attribute__((annotate("$clingAutoload$biodynamo.h")))  VectorField;}
namespace bdm{class __attribute__((annotate("$clingAutoload$moving_cell.h")))  Moving_cell;}
namespace bdm{struct Move;}
namespace bdm{class CellCellForce;}
namespace bdm{struct DissipativeForce;}
namespace bdm{struct TrackPosition;}
namespace bdm{struct SimParam;}
namespace bdm{template <typename T> class __attribute__((annotate("$clingAutoload$core/container/agent_vector.h")))  __attribute__((annotate("$clingAutoload$core/environment/uniform_grid_environment.h")))  AgentVector;
}
namespace bdm{class __attribute__((annotate("$clingAutoload$core/environment/morton_order.h")))  __attribute__((annotate("$clingAutoload$core/environment/uniform_grid_environment.h")))  MortonOrder;}
namespace bdm{struct __attribute__((annotate("$clingAutoload$core/operation/bound_space_op.h")))  __attribute__((annotate("$clingAutoload$core/operation/mechanical_forces_op.h")))  BoundSpace;}
namespace bdm{class __attribute__((annotate("$clingAutoload$core/operation/mechanical_forces_op.h")))  MechanicalForcesOp;}
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "libunitmItestmImechanicsmItwomIcells_dict dictionary payload"

#ifndef BDMSYS
  #define BDMSYS /Users/hp024/biodynamo_relativeAdditionalRadiusForce/build
#endif
#ifndef USE_MPI
  #define USE_MPI 1
#endif
#ifndef USE_DICT
  #define USE_DICT 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#ifndef BEHAVIOURS_H_
#define BEHAVIOURS_H_

#include "core/behavior/behavior.h"
#include "biodynamo.h"
#include "moving_cell.h"

namespace bdm {

struct Move : public Behavior {
  BDM_BEHAVIOR_HEADER(Move, Behavior, 1);

  Move() { AlwaysCopyToNew(); }

  void Run(Agent* a) override {
    if (auto* cell = bdm_static_cast<Moving_cell*>(a)) {
      if (distance_covered.Norm()<=10.)
      // if (a->GetDisplacement().Norm() == 0.0)
      {
      cell->ApplyDisplacement(cell->GetSpeed());
      distance_covered += cell->GetSpeed();
    } else {
      cell->SetSpeed({0.0, 0.0, 0.0});
    }
  }
  }
  Double3 distance_covered = {0.0, 0.0, 0.0};
};

}  // namespace bdm

#endif  // BEHAVIOURS_H_// -----------------------------------------------------------------------------
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

#ifndef CELL_CELL_FORCE_H_
#define CELL_CELL_FORCE_H_

#include "biodynamo.h"
#include "core/interaction_force.h"

namespace bdm {

class CellCellForce : public InteractionForce {
 public:
  CellCellForce() {}
  virtual ~CellCellForce() {}

  virtual Real4 Calculate(const Agent* lhs, const Agent* rhs) const override;
};

}  // namespace bdm

#endif
#ifndef CUSTOM_OPS_H_
#define CUSTOM_OPS_H_

#include "biodynamo.h"
#include "moving_cell.h"

namespace bdm {

struct DissipativeForce : public AgentOperationImpl {
  BDM_OP_HEADER(DissipativeForce);

  void operator()(Agent* agent) override {
    if (auto* cell = bdm_static_cast<Moving_cell*>(agent)) {
      Double3 decrease_speed = cell->GetSpeed() * (-friction_coefficient_);

      cell->UpdateSpeed(decrease_speed);
    }
  }

  double friction_coefficient_ = 0.;
};

struct TrackPosition : public AgentOperationImpl {
  BDM_OP_HEADER(TrackPosition);

  // GetUid()

  void operator()(Agent* agent) override {
    if (auto* cell = bdm_static_cast<Moving_cell*>(agent)) {
      (*positions_)[cell->GetId()].push_back(cell->GetPosition());
    }
  }

  std::vector<std::vector<Double3>>* positions_;
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
  explicit Moving_cell(const Double3& position) : Base(position) {}
  virtual ~Moving_cell() {}

  Double3 GetSpeed() { return speed_; }

  void SetSpeed(Double3 speed) { speed_ = speed; }

  void UpdateSpeed(Double3 delta_speed) { speed_ += delta_speed; }

  void SetId(int id) { id_ = id; }

  int GetId() { return id_; }

 private:
  // 10 um/min -> 1um/0.1 min
  Double3 speed_ = {0.0, 0.0, 0.0};
  int id_ = 0;
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

#ifndef SIM_PARAM_H_
#define SIM_PARAM_H_

#include "biodynamo.h"

namespace bdm {

// Parameters specific for this simulation
struct SimParam : public ParamGroup {
  BDM_PARAM_GROUP_HEADER(SimParam, 1);

  // Forces: attraction coeff default 1, unit is mass/time^2 or N/m
  real_t attraction_coeff = 1*std::pow(10, -12);

  // Forces: repulsion coeff default 2, unit is mass/time^2 or N/m
  real_t repulsion_coeff = 2*std::pow(10, -12);


};

}  // namespace bdm

#endif  // SIM_PARAM_H_
// -----------------------------------------------------------------------------
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
#ifndef UNIT_TEST_MECHANICS_TWO_CELLS_H_
#define UNIT_TEST_MECHANICS_TWO_CELLS_H_

#include "behaviours.h"
#include "biodynamo.h"
#include "custom_ops.h"
#include "moving_cell.h"
#include "cell_cell_force.h"
#include "core/environment/uniform_grid_environment.h"
#include "core/interaction_force.h"
#include "core/operation/mechanical_forces_op.h"
#include "sim_param.h"

namespace bdm {

inline int Simulate(int argc, const char** argv) {
  auto set_param = [](auto* param) {
    // Closed domain, 27 voxel (3x3x3), voxel size = 20um per side
    param->bound_space = Param::BoundSpaceMode::kClosed;
    param->min_bound = -30;
    param->max_bound = 30;
    param->export_visualization = false;
    param->visualize_agents["Moving_cell"] = {};
    param->statistics = true;
    param->simulation_time_step = 0.1;
    param->simulation_max_displacement = 100.0;  // um
  };
  
  // Before we create a simulation we have to tell BioDynaMo about
  // the new parameters.
  Param::RegisterParamGroup(new SimParam());

  Simulation simulation(argc, argv, set_param);
  auto* scheduler = simulation.GetScheduler();

  double const cell_diameter = 10.;  // um
  double const PI = 3.14159265;
  double const cell_volume = 4. / 3. * PI * pow(cell_diameter / 2., 3);  // um^3
  double const cell_density = pow(10, -15);  // 1kg/m^3 = 10^-15g/um^3
  double const cell_mass = cell_volume * cell_density;
  int number_of_cells = 2;

  auto* rm = simulation.GetResourceManager();
  auto* cell1 = new Moving_cell({-15.0, 0.0, 0.0});  // Cells' centers 30um
                                                     // apart
  auto* cell2 = new Moving_cell({15.0, 0.0, 0.0});
  cell1->SetDiameter(10.);
  cell1->SetMass(cell_mass);
  cell1->SetSpeed({1.0, 0.0, 0.0});  // Movement along x-axis, 1um/0.1min
  cell1->AddBehavior(new Move());
  cell1->SetId(0);
  cell2->SetDiameter(10.);
  cell2->SetMass(cell_mass);
  cell2->SetSpeed(
      {-1.0, 0.0,
       0.0});  // Movement along x-axis, negative directions 1um/0.1min
  cell2->AddBehavior(new Move());
  cell2->SetId(1);

  rm->AddAgent(cell1);
  rm->AddAgent(cell2);

  // Track positions
  const int time_steps = 100;

  std::vector<std::vector<Double3>> cell_positions(number_of_cells);
  auto* track_pos_op = NewOperation("track_position");
  track_pos_op->GetImplementation<TrackPosition>()->positions_ =
      &cell_positions;
  track_pos_op->frequency_ = 1;  // 0.1 min
  scheduler->ScheduleOp(track_pos_op);

  // Move behaviour
  auto* behavior_op = scheduler->GetOps("behavior")[0];
  behavior_op->frequency_ = 1;  // Set behaviors' frequency

  // Custom force module
  auto* custom_force = new CellCellForce();
  auto* mech_op = scheduler->GetOps("mechanical forces")[0];
  auto* force_implementation = mech_op->GetImplementation<MechanicalForcesOp>();
  force_implementation->SetInteractionForce(custom_force);
  mech_op->frequency_ = 1;

  // Run simulation for 10 minutes (100 steps, 1 step = 0.1 min )
  scheduler->Simulate(time_steps);

  std::cout << "Simulation completed successfully!" << std::endl;

  std::ofstream file;
  if (!file.is_open()) {
    file.open("positions.csv");
  }

  for (size_t j = 0; j < time_steps; j++) {
    for (size_t i = 0; i < cell_positions.size(); i++) {
      file << j << "\t " << cell_positions[i][j];
    }
    file << std::endl;
  }

  file.close();

  return 0;
}

}  // namespace bdm

#endif  // UNIT_TEST_MECHANICS_TWO_CELLS_H_

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"", payloadCode, "@",
"bdm::AgentPointer<bdm::Agent>", payloadCode, "@",
"bdm::AgentVector<bdm::AgentHandle>", payloadCode, "@",
"bdm::BoundSpace", payloadCode, "@",
"bdm::CellCellForce", payloadCode, "@",
"bdm::DissipativeForce", payloadCode, "@",
"bdm::Environment", payloadCode, "@",
"bdm::FixedSizeVector<ULong64_t,27>", payloadCode, "@",
"bdm::FixedSizeVector<const bdm::UniformGridEnvironment::Box*,27>", payloadCode, "@",
"bdm::FixedSizeVector<unsigned long,14>", payloadCode, "@",
"bdm::Functor<void,bdm::Iterator<ULong64_t>*>", payloadCode, "@",
"bdm::InPlaceExecutionContext", payloadCode, "@",
"bdm::MechanicalForcesOp", payloadCode, "@",
"bdm::MortonOrder", payloadCode, "@",
"bdm::Move", payloadCode, "@",
"bdm::Moving_cell", payloadCode, "@",
"bdm::ParallelResizeVector<bdm::UniformGridEnvironment::Box>", payloadCode, "@",
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
"bdm::SimParam", payloadCode, "@",
"bdm::TrackPosition", payloadCode, "@",
"bdm::UniformGridEnvironment", payloadCode, "@",
"bdm::UniformGridEnvironment::Adjacency", payloadCode, "@",
"bdm::UnorderedFlatmap<TClass*,vector<bdm::Agent*> >", payloadCode, "@",
"bdm::VectorField", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("libunit-test-mechanics-two-cells_dict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_libunitmItestmImechanicsmItwomIcells_dict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_libunitmItestmImechanicsmItwomIcells_dict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_libunitmItestmImechanicsmItwomIcells_dict() {
  TriggerDictionaryInitialization_libunitmItestmImechanicsmItwomIcells_dict_Impl();
}
