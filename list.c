#include <stdio.h>
#include <stdlib.h>

#include <CoreFoundation/CoreFoundation.h>
#include <VideoToolbox/VideoToolbox.h>
#include <VideoToolbox/VTVideoEncoderList.h>
#include <CoreMedia/CoreMedia.h>


int main() {
    CFArrayRef encoder_list;
    VTCopyVideoEncoderList(NULL, &encoder_list);
    CFIndex size = CFArrayGetCount(encoder_list);
    
    for (CFIndex i = 0; i < size; i++) {
        CFDictionaryRef encoder_dict = CFArrayGetValueAtIndex(encoder_list, i);
        
#define VT_PRINT(key, name) \
        CFStringRef name##_ref = CFDictionaryGetValue(encoder_dict, key); \
        CFIndex name##_len = CFStringGetLength(name##_ref);               \
        char *name = malloc(name##_len + 1);                              \
        memset(name, 0, name##_len + 1); \
        CFStringGetFileSystemRepresentation(name##_ref, name, name##_len);
        
        VT_PRINT(kVTVideoEncoderList_EncoderName, name);
        printf("Name: %s\n", name);
        VT_PRINT(kVTVideoEncoderList_DisplayName, dn);
        printf("Display Name: %s\n", dn);
        VT_PRINT(kVTVideoEncoderList_EncoderID, id);
        printf("Id: %s\n", id);
        
        printf("=========================\n");
    }
    
    CFRelease(encoder_list);
    
    exit(0);
}
