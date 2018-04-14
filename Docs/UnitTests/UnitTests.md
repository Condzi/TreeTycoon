# Unit Test
Contains tests submodules from every module.
## Example
```cpp
UNIT_TEST( ModuleA )
{
SUB_TEST( SubModuleA )
{
    Foo boo;
    REQUIRE( boo.somevalue == 1 );
    INFO( "some information" );
};

SUB_TEST( ModuleA, SubModuleB ) { /* ... */ };
}
```
Result:
```
ModuleA, SubModuleA: some information
ModuleA, SubModuleB FAILED: someReason
```
## Enfocements
One unit test consist of many sub tests. If the `REQUIRE( expr )` macro fails, the sub test failes => if doesn't fail, then sub test pass. `INFO( msg )` - just print information to command prompt.