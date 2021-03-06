// 지금까지 내용정리
// Java에서의 디자인 패턴 사용 예제
// http://stackoverflow.com/questions/1673841/examples-of-gof-design-patterns-in-javas-core-libraries

// GoF 디자인 패턴 23가지

// 생성 5가지
//	- 추상 팩토리: 공장을 인터페이스 기반으로 교체 가능하게 하자.
//	- 싱글톤: 하나의 객체를 생성하고, 동일한 방법으로 접근 가능하게 하자.
//	- 팩토리 메소드: 템플릿 메소드와 동일한데 변하는 것이 정책이 아닌 객체 생성일 때
//	- 프로토타입 패턴: 객체의 복제를 다형성 기반으로
//	- 빌더

// 구조 7가지
//	- 어댑터: 클라이언트가 요구하는 클래스를 인터페이스만 변경해서 제공하는 패턴 - stack adapter
//			MVC 모델에서 view의 요구를 controller가 받아서 model 변경, List와 ListView가 있다면 그 사이에 ListAdapter가 중간 역할한다.
//	- 컴포지트: 복합 객체의 구성
//			단일 객체와 복합 객체는 동일 부모를 가져야 한다.
//			사용법이 동일해야 한다.
//	- 플라이웨이트: 속성이 동일한 객체는 공유하자.
//			객체 생성 비용을 줄여 성능을 올리는 방법.
//			불변 객체 활용: 멀티 스레드에서 중요 (Effective Java 참고)
//	- 프록시
//	- 브릿지
//	- 퍼사드
//	- 데코레이터

// 행위 11가지
//	- 컨테이너에 연관된 패턴 2가지
//		반복자: 컨테이너(복합 객체)의 내부 구조에 상관없이 요소 열거
//		반문자:                      '                       연산
//	- 이벤트 처리에 관련된 패턴 2가지
//		관찰자: 발생된 이벤트를 등록된 객체에게 전파
//		책임의 전자: 발생된 이벤트를 다음 객체에게 전달

//	- 공통성과 가변성의 분리 관련된 패턴 2가지
//		템플릿 메소드: 변하는 것을 가상함수로 분리
//		전략: 변하는 것을 인터페이스 기반 클래스로 분리

//	- 커맨드: 명령을 캡슐화
//	- 중재자: 복잡한 객체 간의 관계를 캡슐화
//			GUI를 만드는 것도 복잡한데 각각의 상태가 다른 객체의 상태에 영향을 미치면 더 복잡해짐
//			객체들이 직접적으로 연결되지 않고 중재자로 모이게 만들어줌
//			재사용할 수 없는 코드를 한곳으로 모아줌
//	- 메멘토
//	- 상태
//	- 인터프리터: 언어를 설계할 때 쓰임 - 안 써
