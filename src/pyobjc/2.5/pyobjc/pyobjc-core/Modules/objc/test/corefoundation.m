/* Some testhelpers for CF-type support.
 * XXX: should define our own CF-type for at least the non-tollfree bridged
 * tests to avoid interfering with the real CF-wrappers.
 * XXX: add a second type that isn't tollfree bridged to check that the 
 * default behaviour works as well.
 */
#include "Python.h"
#include "pyobjc-api.h"

#import <Foundation/Foundation.h>
#import <CoreFoundation/CoreFoundation.h>


@interface OC_TestCoreFoundation : NSObject
{
}
// not toll-free bridged. 
+(char*)signatureForCFUUIDRef;
+(CFTypeID)typeidForCFUUIDRef;
+(CFUUIDRef)newUUID;
+(NSString*)formatUUID:(CFUUIDRef)uuid;
+(NSObject*)anotherUUID;

// tollfree bridged:
+(char*)signatureForCFDateRef;
+(CFTypeID)typeidForCFDateRef;
+(CFDateRef)today;
+(NSString*)formatDate:(CFDateRef)date;
+(int)shortStyle;
@end


@implementation OC_TestCoreFoundation

+(char*)signatureForCFUUIDRef
{
	return @encode(CFUUIDRef);
}

+(CFTypeID)typeidForCFUUIDRef;
{
	return CFUUIDGetTypeID();
}

+(CFUUIDRef)newUUID
{
	CFUUIDRef result =  CFUUIDCreate(NULL);

	/* We own a reference, but want to released a borrowed ref. */
	[(NSObject*)result autorelease];

	return result;
}

+(NSObject*)anotherUUID
{
	CFUUIDRef result =  CFUUIDCreate(NULL);

	/* We own a reference, but want to released a borrowed ref. */
	[(NSObject*)result autorelease];

	return (NSObject*)result;
}


+(NSString*)formatUUID:(CFUUIDRef)uuid
{
	NSString* result;

	result = (NSString*)CFUUIDCreateString(NULL, uuid);
	return [result autorelease];
}



+(char*)signatureForCFDateRef;
{
	return @encode(CFDateRef);
}

+(CFTypeID)typeidForCFDateRef;
{
	return CFDateGetTypeID();
}

+(CFDateRef)today;
{
	CFDateRef result;

	result = CFDateCreate(NULL, CFAbsoluteTimeGetCurrent());

	/* We own a reference, but want to released a borrowed ref. */
	[(NSObject*)result autorelease];

	return result;
}

+(NSString*)formatDate:(CFDateRef)date
{
	CFDateFormatterRef formatter = CFDateFormatterCreate(
			NULL, CFLocaleCopyCurrent(), 
			kCFDateFormatterShortStyle, NSDateFormatterNoStyle  );

	NSString* result = (NSString*)CFDateFormatterCreateStringWithDate(
			NULL, formatter, date);

	CFRelease(formatter);
	return [result autorelease];
}

+(int)shortStyle
{
	return kCFDateFormatterShortStyle;
}

@end



static PyMethodDef mod_methods[] = {
	        { 0, 0, 0, 0 }
};

void initcorefoundation(void);
void initcorefoundation(void)
{
	PyObject* m;

	m = Py_InitModule4("corefoundation", mod_methods, NULL, NULL, PYTHON_API_VERSION);

	PyObjC_ImportAPI(m);

	PyModule_AddObject(m, "OC_TestCoreFoundation", 
		PyObjCClass_New([OC_TestCoreFoundation class]));
}
