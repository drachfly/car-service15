/*
 * Copyright (C) 2022 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "CarPowerPolicyServer.h"

#include <fuzzbinder/libbinder_ndk_driver.h>
#include <fuzzer/FuzzedDataProvider.h>
#include <utils/StrongPointer.h>

using ::android::fuzzService;
using ::android::Looper;
using ::android::sp;
using ::android::frameworks::automotive::powerpolicy::CarPowerPolicyServer;
using ::ndk::SharedRefBase;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    sp<Looper> looper(Looper::prepare(/*opts=*/0));
    std::shared_ptr<CarPowerPolicyServer> server = SharedRefBase::make<CarPowerPolicyServer>();
    server->init(looper);
    fuzzService(server->asBinder().get(), FuzzedDataProvider(data, size));
    return 0;
}
