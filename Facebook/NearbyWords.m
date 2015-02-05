#import <Foundation/Foundation.h>

@interface NearbyWords: NSObject

- (NearbyWords*) initWithNearbyCharacters: (NSDictionary*) nearbyChars;
- (NSArray*) nearbyWords: (NSString*) word;

@end

@interface NearbyWords()
@property (nonatomic, strong) NSDictionary *nearbyChars;
@end

@implementation NearbyWords

- (NearbyWords*) initWithNearbyCharacters: (NSDictionary*) nearbyChars
{
	self = [super init];
	if(self){
		_nearbyChars = nearbyChars;
	}
	return self;
}

- (NSArray*) nearbyWords: (NSString*) word
{
	NSMutableArray *words = [NSMutableArray new];
	NSMutableString *temp = [[NSMutableString alloc] initWithString: word];
	[self findWords: word position: 0 temp: temp storage: words];
	
	return [NSArray arrayWithArray: words];
}

- (void) findWords: (NSString*) original position: (NSInteger) position temp: (NSMutableString*) temp storage: (NSMutableArray*) storage
{
	if(position >= [original length]) 
	{
		[storage addObject: [NSString stringWithString: temp]];
		return;
	}
	
	NSString *ch = [original substringWithRange: NSMakeRange(position, 1)];
	NSArray *nearby = self.nearbyChars[ch];
	
	for(NSString *nearbyCh in nearby)
	{
		[temp replaceCharactersInRange: NSMakeRange(position, 1) withString: nearbyCh];
		[self findWords: original position: position + 1 temp: temp storage: storage];
	}
}

@end

int main(int argc, char *argv[]) {
	@autoreleasepool {
		
		NSDictionary *nearbyChars = @{
			@"g" : @[@"g", @"h", @"f"],
			@"i" : @[@"i", @"o", @"k"]
		};
		
		NearbyWords *words = [[NearbyWords alloc] initWithNearbyCharacters: nearbyChars];
		NSArray *answer = [words nearbyWords: @"gi"];
		NSLog(@"%@", answer);
	}
}