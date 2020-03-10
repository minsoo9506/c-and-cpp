### 20.1 비주얼 스튜디오 프로파일링
- 주로 성능 최적화를 위해 한다. (**Diagnostic Tools** 이용)
  - cpu가 일하는 부분을 디버그해서 최적화할 수 있는 부분을 본다.
  - memory도 마찬가지이다.
- 8:2의 법칙 : cpu가 많이 일하는 부분에 8의 노력 나머지에 2의 노력을 쏟아부어서 최적화해라!
- 프로그래밍 스킬보다 알고리즘 레벨에서 최적화 하는 것이 더 좋다.
- cpu
  -  break point를 지정하고 디버그 모드에서 diagnostic tools를 이용한다.
  - 거기에 CPU usage가 있는데 ~exe 이 부분을 클릭하면 상세히 CPU 활동을 볼 수 있다.
- memory
  - 디버그 모드에서 diagnostic tools를 이용한다.
  - break point를 지정하고 하나씩 디버그(Continue)하면서 Take Snapshot하면 해당 시점에서 메모리 상태를 보여준다.
- 이전까지는 디버그 모드였는데 releas모드도 프로파일링 가능하다.
  - 실제로 releaes가 더 중요할 수도 있다. 디버그 모드와 releaes는 조금 다르기 때문에!
  - Debug 메뉴에서 Perfomance profiler 라는 메뉴 이용

### 20.2 Git, Github

### 20.3 비주얼 스튜디오에서 깃헙 사용하기
- github plugin 설치해서 사용할 수 있다.
  - extension and updates -> online -> github -> 설치 -> 재시작
  - 근데 꼬이는 경우가 꽤 있어서 CLI 작동법을 아는게 좋다.

### 20.4 Vcpkg
- python에서 외부라이브러리 설치하듯 cpp에서도 가능하다.
- 구글에 Vcpkg를 검색하면 된다.
  - git clone 하고 설치한 뒤에
  - 원하는 라이브러리 설치하여 사용한다.
  - vcpk.exe install 라이브러리이름:x64-windows (특정 라이브러리를 64용 windows 설치하겠다)
  - 위에서 : 뒷부분은 항상 필요한 것은 아니다. option~

### 20.5 TCP/IP 네트워킹 맛보기
- 강의 참고 (네트워크 관련이라 잘모르겠다)
- boost/asio
- 서버와 클라이언트 toy project 개발

### 20.6 외부 라이브러리 설치, 프로젝트 템플릿
- NanoGUI 사례
  - NanoGUI가 외부 라이브러리를 많이 사용하는 GUI 프로그램이다
  - 그래서 설치방법을 연습해본다
  - NanoGUI git clone
  - CMake 설치
  - 나머지는 동영상 참고
- vcpk를 사용하지 않고 외부라이브러리 설치하기
