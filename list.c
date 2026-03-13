#include <stdio.h>

#include <CoreFoundation/CoreFoundation.h>
#include <VideoToolbox/VideoToolbox.h>
#include <VideoToolbox/VTVideoEncoderList.h>

static const char *cfstr_to_cstr(CFStringRef str) {
    const char *ptr = CFStringGetCStringPtr(str, kCFStringEncodingUTF8);
    if (ptr)
        return ptr;

    CFIndex len = CFStringGetMaximumSizeForEncoding(
        CFStringGetLength(str), kCFStringEncodingUTF8) + 1;
    char *buf = malloc(len);
    if (!CFStringGetCString(str, buf, len, kCFStringEncodingUTF8)) {
        free(buf);
        return "(encoding error)";
    }
    return buf;
}

int main(void) {
    CFArrayRef encoder_list = NULL;
    VTCopyVideoEncoderList(NULL, &encoder_list);

    CFIndex count = CFArrayGetCount(encoder_list);
    for (CFIndex i = 0; i < count; i++) {
        CFDictionaryRef dict = CFArrayGetValueAtIndex(encoder_list, i);

        CFStringRef keys[] = {
            kVTVideoEncoderList_EncoderName,
            kVTVideoEncoderList_DisplayName,
            kVTVideoEncoderList_EncoderID,
        };
        const char *labels[] = {"Name", "Display Name", "Id"};

        for (int k = 0; k < 3; k++) {
            CFStringRef val = CFDictionaryGetValue(dict, keys[k]);
            if (val)
                printf("%s: %s\n", labels[k], cfstr_to_cstr(val));
        }
        printf("=========================\n");
    }

    CFRelease(encoder_list);
    return 0;
}
