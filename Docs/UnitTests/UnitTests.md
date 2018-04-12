# Unit Test
Contains tests submodules from every module.
## Example
The goal is to make whole unit test look like this.
```cpp
SUB_TEST( ModuleA, SubModuleA )
{
    Foo boo;
    if ( boo.failed )
        return TEST_FAILED( "reason" );

    INFO( "some information" );
    // ...
    return TEST_PASSED;
}
SUB_TEST( ModuleA, SubModuleB ) { /* ... */ }
```
Result:
```
ModuleA, SubModuleA: some information
ModuleA, SubModuleB FAILED: someReason
```