이 문서에서는 cpp 에서 사용되는 반복자에 대해 정리한다.

### Regular iterator for loop
숫자를 기반으로 반복하는 for loop 이다.
대표적인 루프이나, 실수로 인해 오류가 발생할 수 있다.
``` cpp
for (int i = 0; i < n; ++i)
{
    // do something
}
```
아래의 범위기반 반복은 더 간단하고 안전하게 반복하는 방법을 제공한다.

### Range-based for loop
범위를 기반으로 반복하는 for loop 이다. 안전하게 모든 요소를 반복한다.

syntax
``` cpp
attr (optional) : 옵션
for ( init-statement(optional) range-declaration: range-expression ){
    loop-statement(do something)
}
```
const를 붙여, 매번 반복하는 동안 range-expression을 복사하지 않도록 할 수 있다.
``` cpp
for (const auto& x : v)
{
    // do something
}
```
단순히 `for(auto x : v)` 와 같이 사용하면, deep copy가 발생할 수 있다. 종합적으로 const 참조로 접근하는 것이 가장 좋다.
### std::for each(<algorithm>)
std::algorithm 에서 제공하는 for each 함수이다.
` for_each( InputIt first, InputIt last, UnaryFunction f ); `
sort와 유사하게, 첫번째 인자로 시작 반복자, 두번째 인자로 끝 반복자, 세번째 인자로 lambda(함수)를 받는다. 요소를 input으로 함수를 반복해서 실행한다.
``` cpp
for_each(v.begin(), v.end(), [](int x) { cout << x << " "; });
```
람다식이 필요한 반복문이다.

for each_n(<algorithm> 은 c++17 부터 제공)
해당 함수는 위의 함수와 다르게 시작에서 몇번 반복될지 정할 수 있다.
` for_each_n( InputIt first, Size n, UnaryFunction f ); `
첫번째 인자로 시작 반복자, 두번째 인자로 반복 횟수, 세번째 인자로 lambda(함수)를 받는다. 요소를 input으로 함수를 반복해서 실행한다.
``` cpp
for_each_n(v.begin(), 3, [](int x) { cout << x << " "; });
```
### std::transform(<algorithm>)
std::algorithm 에서 제공하는 transform 함수이다.
다른 반복자와 주요한 차이점은 결과를 다른 컨테이너에 저장한다.
` transform( InputIt first1, InputIt last1, OutputIt d_first, UnaryOperation unary_op ); `
첫번째 인자로 시작 반복자, 두번째 인자로 끝 반복자, 세번째 인자로 시작 반복자, 네번째 인자로 함수를 받는다. 요소를 input으로 함수를 반복해서 실행한 결과를 output으로 저장한다.
``` cpp
transform(v.begin(), v.end(), v.begin(), [](int x) { return x * x; });
```