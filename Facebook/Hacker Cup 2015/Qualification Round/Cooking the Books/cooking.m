#import <Foundation/Foundation.h>

int findSmall(NSString *x)
{
	char * s = [x UTF8String];
	
	for(int i = 0; i < [x length]; i++)
	{
		char f = s[i];
		int f_v = f - '0';
		int min = 11;
		int index = -1;
		
		for(int j = i + 1; j < [x length]; j++)
		{
			char ch = s[j];
			int f_ch = ch - '0';
			if(f_ch < min && f_ch != 0) {
				min = f_ch;
				index = j;
			}
		}
		
		if(min < f_v) {
			char temp = s[i];
			s[i] = s[index];
			s[index] = temp;
			break;
		}
	}
	
	return atoi(s);
}

int findLarge(NSString *x)
{
	char * s = [x UTF8String];
	
	for(int i = 0; i < [x length]; i++)
	{
		char f = s[i];
		int f_v = f - '0';
		int max = -1;
		int index = -1;
		
		for(int j = [x length] - 1; j > i ; j--)
		{
			char ch = s[j];
			int f_ch = ch - '0';
			if(f_ch > max) {
				max = f_ch;
				index = j;
			}
		}
		
		if(max > f_v) {
			char temp = s[i];
			s[i] = s[index];
			s[index] = temp;
			break;
		}
	}
	
	return atoi(s);
}

void handleCase(NSString *string, int caseNumber)
{
	int large = findLarge(string);
	int small = findSmall(string);
	NSLog(@"Case #%i %i %i", caseNumber, small, large);
}

int main(int argc, char *argv[]) {
	@autoreleasepool {
		
		if(argc != 2)
		{
			NSLog(@"Wrong number of parameters.");
			return -1;
		} 
		else 
		{	
			NSString *path = [NSString stringWithCString: argv[1] encoding: NSUTF8StringEncoding];
			NSString *contents = [NSString stringWithContentsOfFile: path encoding: NSUTF8StringEncoding error: nil];
			contents = [contents stringByTrimmingCharactersInSet: [NSCharacterSet newlineCharacterSet]];
			
			NSArray *elements = [contents componentsSeparatedByCharactersInSet: [NSCharacterSet newlineCharacterSet]];
			NSLog(@"%@", elements);
			
			int numberOfCases = atoi([elements[0] UTF8String]);
			
			for(int i = 0; i < numberOfCases; i++)
			{
				handleCase(elements[i+1], i+1);
			}
		}	
	}
}