# ArcanoidSrc
В данном проекте использовался подход "C++ код расширенный в Blueprints".
(Конечно, данный проект тривиален и мог быть написан с использование только Blueprint или только C++) 

Основная идея сделать гибкий и расширяемый фреймворк для создания арканоид побобных игр.
Были имплементированы следующие инструменты:

ArcanoidPawn - основной клас представляющий игрока.
Он включает всебя:
	Platform - платформу двигающуюся по рельсам. 
	Rails(рельсы) - это сплайн по которому движется платформа. Его можно уникально настроить для каждого уровня.
	SpringArm и Camera - позволяют легко и удобно менять положение камеры индивидуально для каждого уровня.
	World Border - сфера ограничивающая игровое пространстов. Ball(шарик) который покижает сферу самоуничтожается.

Ball - игровой шарик. Их может быть несколько. Если все шарики покинули пределы WorldBorder - то игроку заcчитывается фейл(отнимается жизнь, засчитывается пройграш etc.)

Wall - неразрушаемая стенка ограничивающая уровень. Могут быть различной формы в зависимости от StaticMesh.
		
Brick - разрушаемый кирпич.

Pickup - различные бонусы. 
	
BrickGenerator - генератор больших обьемов кирпичей для облегчения работы гейм дизайнера. Пример работы с Blueprints на уровне редактора.
