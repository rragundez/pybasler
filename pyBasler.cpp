#include <boost/python.hpp>
#include <pylon/PylonIncludes.h>
#include <sstream>
#include <iostream>
#include <string>

#ifdef PYLON_WIN_BUILD
#include <pylon/PylonGUI.h>
#endif

using namespace Pylon;
using namespace std;

string capture()
{
    CPylonImage image;
    CImageFormatConverter fc;
    CGrabResultPtr ptrGrabResult;

    // Automagically call PylonInitialize and PylonTerminate to ensure
    // the pylon runtime system is initialized during the lifetime of this object.
    Pylon::PylonAutoInitTerm autoInitTerm;

    try
    {
        CInstantCamera camera( CTlFactory::GetInstance().CreateFirstDevice());
        cout << "\nUsing device " << camera.GetDeviceInfo().GetModelName() << endl;

        camera.Open();
        camera.StartGrabbing();

        fc.OutputPixelFormat = PixelType_RGB8packed;
        camera.RetrieveResult( 5000, ptrGrabResult, TimeoutHandling_ThrowException);

        if (ptrGrabResult->GrabSucceeded()){
            fc.Convert(image, ptrGrabResult);
            unsigned char* img = (unsigned char*)image.GetBuffer();
            string string_bytes;
            string_bytes.append(reinterpret_cast<const char*> (img));
            return string_bytes;
        }
        else {
            cout << "\nCould not grab image" << endl;
            return "FAIL";
        }
    }catch(...){
        cout << "\nThere are no active devices" << endl;
        return "FAIL";
    }
}

BOOST_PYTHON_MODULE(pyBasler)
{
    using namespace boost::python;
    def("capture", capture);
}
