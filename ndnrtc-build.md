### webrtc library
Unlike webrtc on OS X, these webrtc libraries are not in a flat folder. They are in the following paths. 

```
/home/jcw/webrtc/src/out/Release 
/home/jcw/webrtc/src/out/Release/obj/webrtc 
/home/jcw/webrtc/src/out/Release/obj/webrtc/modules/video_coding/codecs/vp9 
/home/jcw/webrtc/src/out/Release/obj/webrtc/modules/video_coding/codecs/vp8 
/home/jcw/webrtc/src/out/Release/obj/webrtc/video_engine 
/home/jcw/webrtc/src/out/Release/obj/webrtc/system_wrappers 
/home/jcw/webrtc/src/out/Release/obj/webrtc/base 
/home/jcw/webrtc/src/out/Release/obj/webrtc/tools 
/home/jcw/webrtc/src/out/Release/obj/chromium/src/third_party/libjpeg_turbo 
/home/jcw/webrtc/src/out/Release/obj/chromium/src/third_party/opus 
/home/jcw/webrtc/src/out/Release/obj/chromium/src/third_party/protobuf 
/home/jcw/webrtc/src/out/Release/obj/webrtc/voice_engine 
/home/jcw/webrtc/src/out/Release/obj/webrtc/modules/video_coding/utility 
/home/jcw/webrtc/src/out/Release/obj/chromium/src/third_party/libvpx 
/home/jcw/webrtc/src/out/Release/obj/webrtc/modules 
/home/jcw/webrtc/src/out/Release/obj/webrtc/common_video 
/home/jcw/webrtc/src/out/Release/obj/webrtc/common_audio 
/home/jcw/webrtc/src/out/Release/obj/webrtc/test 
```
There are objects files in these foler which is necessary for these libraries (*.a)which are thin archives. 
We need to convert them to normal static library:
```
for lib in `find . -name '*.a'`;
    do ar -t $lib | xargs ar rvs $lib.new && mv -v $lib.new $lib;
done

#copy to a flat folder
mkdir  /home/jcw/webrtc/src/out/Release/alllib
for lib in `find . -name '*.a'`;
    do cp $lib /home/jcw/webrtc/src/out/Release/alllib;# provide this path as WEBRTCLIB to config.site of ndnrtc
done

```
ref: [here](https://stackoverflow.com/questions/25554621/turn-thin-archive-into-normal-one)
ref: [here](https://code.google.com/p/webrtc/issues/detail?id=5022)


// this is the working version for Zhehao based on Jiachen's image. May or may not work for others, or have runtime errors as it's being tested

// Please compile webrtc, openfec, boost, ndn-cpp and other dependencies before moving on to this.

### NDN-CPP-0.7 

(without boost:: specification for int64_t definition as in Jiachne's version; Unverified for now.)
```
./configure --with-std-shared-ptr=no --with-std-function=no --with-boost-libdir=/home/jcw/boost_1_54_0/build/lib --prefix=$(pwd)/build
make
make install
```

### NDN-RTC
in CPP folder, 
```
./configure —prefix=$(pwd)/build
```
Contents of ./build/share/config.site:
```
WEBRTCDIR=/home/jcw/webrtc/src 
WEBRTCSRC=/home/jcw/webrtc/src/webrtc 
WEBRTCLIB=/home/jcw/webrtc/src/out/Release/alllib

OPENFECDIR=/home/jcw/openfec_v1.4.2 
OPENFECSRC=/home/jcw/openfec_v1.4.2/src 
OPENFECLIB=/home/jcw/openfec_v1.4.2/bin/Release

NDNCPPDIR=/home/jcw/ndn-cpp-zhehao/include 
NDNCPPLIB=/home/jcw/ndn-cpp-zhehao/.libs

BOOSTDIR=/home/jcw/boost_1_54_0/build/include 
BOOSTLIB=/home/jcw/boost_1_54_0/build/lib
```
And afterwards
```
make
```
For now, replace the second last step of make, which generates libndnrtc.so (the command with "gcc -shared") with
```
g++  -fPIC -DPIC -shared -nostdlib /usr/lib/gcc/x86_64-linux-gnu/4.9/../../../x86_64-linux-gnu/crti.o /usr/lib/gcc/x86_64-linux-gnu/4.9/crtbeginS.o  src/.libs/libndnrtc_la-audio-capturer.o src/.libs/libndnrtc_la-audio-consumer.o src/.libs/libndnrtc_la-audio-playout.o src/.libs/libndnrtc_la-audio-renderer.o src/.libs/libndnrtc_la-audio-thread.o src/.libs/libndnrtc_la-av-sync.o src/.libs/libndnrtc_la-buffer-estimator.o src/.libs/libndnrtc_la-base-capturer.o src/.libs/libndnrtc_la-chase-estimation.o src/.libs/libndnrtc_la-consumer.o src/.libs/libndnrtc_la-external-capturer.o src/.libs/libndnrtc_la-face-wrapper.o src/.libs/libndnrtc_la-fec.o src/.libs/libndnrtc_la-frame-buffer.o src/.libs/libndnrtc_la-frame-data.o src/.libs/libndnrtc_la-interest-queue.o src/.libs/libndnrtc_la-jitter-timing.o src/.libs/libndnrtc_la-media-thread.o src/.libs/libndnrtc_la-media-stream.o src/.libs/libndnrtc_la-name-components.o src/.libs/libndnrtc_la-ndn-assembler.o src/.libs/libndnrtc_la-ndnrtc-library.o src/.libs/libndnrtc_la-ndnrtc-namespace.o src/.libs/libndnrtc_la-ndnrtc-object.o src/.libs/libndnrtc_la-ndnrtc-utils.o src/.libs/libndnrtc_la-pipeliner.o src/.libs/libndnrtc_la-playout.o src/.libs/libndnrtc_la-rate-control.o src/.libs/libndnrtc_la-realtime-arc.o src/.libs/libndnrtc_la-rtt-estimation.o src/.libs/libndnrtc_la-segmentizer.o src/.libs/libndnrtc_la-session.o src/.libs/libndnrtc_la-simple-log.o src/.libs/libndnrtc_la-statistics.o src/.libs/libndnrtc_la-video-coder.o src/.libs/libndnrtc_la-video-consumer.o src/.libs/libndnrtc_la-video-decoder.o src/.libs/libndnrtc_la-video-playout.o src/.libs/libndnrtc_la-video-renderer.o src/.libs/libndnrtc_la-video-thread.o src/.libs/libndnrtc_la-webrtc-audio-channel.o   -Wl,-rpath -Wl,/home/jcw/ndn-cpp/.libs -Wl,-rpath -Wl,/home/jcw/ndn-cpp/build/lib -L/home/jcw/ndn-cpp/.libs -L/home/jcw/openfec_v1.4.2/bin/Release -L/home/jcw/webrtc/src/out/Release/alllib -L/home/jcw/boost_1_54_0/build/lib /home/jcw/ndn-cpp/.libs/libndn-cpp.so -lopenfec -lboost_system -lboost_timer -lboost_chrono -lboost_thread -L/usr/lib/gcc/x86_64-linux-gnu/4.9 -L/usr/lib/gcc/x86_64-linux-gnu/4.9/../../../x86_64-linux-gnu -L/usr/lib/gcc/x86_64-linux-gnu/4.9/../../../../lib -L/lib/x86_64-linux-gnu -L/lib/../lib -L/usr/lib/x86_64-linux-gnu -L/usr/lib/../lib -L/usr/lib/gcc/x86_64-linux-gnu/4.9/../../.. -lstdc++ -lm -lc -lgcc_s /usr/lib/gcc/x86_64-linux-gnu/4.9/crtendS.o /usr/lib/gcc/x86_64-linux-gnu/4.9/../../../x86_64-linux-gnu/crtn.o  -O2 -Wl,--whole-archive -laudio_coding_module -laudio_decoder_interface -lCNG -lG711 -lG722 -liLBC -lPCM16B -laudio_encoder_interface -laudio_conference_mixer -laudioproc_debug_proto -laudio_device -laudio_processing -laudio_processing_sse2 -lbitrate_controller -lchannel_transport -lcommon_audio -lcommon_audio_sse2 -lcommon_video -ldesktop_capture -ldesktop_capture_differ_sse2 -lframe_editing_lib -lframe_generator -lhistogram -ljpeg_turbo -liSAC -lmedia_file -lmetrics -lneteq -lopus -lpaced_sender -lprotobuf_lite -lrtp_rtcp -lrtc_base_approved -lsystem_wrappers -lvideo_capture_module -lvideo_coding_utility -lvideo_engine_core -lvideo_processing -lvideo_processing_sse2 -lvideo_quality_analysis -lvideo_render_module -lvideo_render_module_internal_impl -lvoice_engine -lvpx -lvpx_intrinsics_avx2 -lvpx_intrinsics_mmx -lvpx_intrinsics_sse2 -lvpx_intrinsics_ssse3 -lvpx_intrinsics_sse4_1 -lwebrtc_i420 -lwebrtc_opus -lwebrtc_utility -lwebrtc_video_coding -lwebrtc_vp8 -lwebrtc_vp9 -lwebrtc_common -lwebrtc -lyuv -lremote_bitrate_estimator -lvideo_capture -lrtc_base -lgtest -ljsoncpp -lred -lfield_trial -lopenmax_dl -Wl,--no-whole-archive   -Wl,-soname -Wl,libndnrtc.so.0 -o .libs/libndnrtc.so.0.0.0
```
In the webrtc linked libs, following libraries are newly added; since without them -lndnrtc in the app would complain about undefined symbols from webrtc; -l them when compiling the app would probably result in duplicated symbols:
```
-lremote_bitrate_estimator -lvideo_capture -lrtc_base -lgtest -ljsoncpp -lred -lfield_trial -lopenmax_dl
```
While other webrtc static libraries are _manually_ included in -Wl,--whole-archive ... -Wl,--no-whole-archive; check configure.ac for correct flags for shared object generation.

### The application (Code attached)
```
g++ -std=c++11 test_ndnrtc_getversion.cpp -o test_getversion -L. -lndn-cpp -L/home/jcw/ndn-cpp-zhehao/build/lib -I/home/jcw/ndn-cpp-zhehao/build/include -lndnrtc -lX11 -lXdamage -lXrender -lXext -lnss3 -lssl3 -lXfixes -lXcomposite 2>&1
```
Following links are added because of undefined symbol from NDN-RTC; these were probably dynamic linked by webrtc; found their symbols by nm'ing the libraries in system directory.
```
-lX11 -lXdamage -lXrender -lXext -lnss3 -lssl3 -lXfixes -lXcomposite
```
With these the app compiled successfully; 

Expect to see a ndnrtc-startup.log in the same folder where you run the app.


No. 1 problem we had would be using a shared object that links to static libraries; Then just resolving further undefined symbols as needed.

Worth mentioning that this is the expected behavior on Linux: [This question](http://stackoverflow.com/questions/14889941/link-a-static-library-to-a-shared-one-during-build), and other ones from similar topic, helped.

My suspect is that on OSX it's either taken care of by XCode/build systems; Or a different ld program strategy?
