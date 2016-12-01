.name "the professor"
.comment "My guy in D.C. tells me that we are not dealing with a student here, we're dealing with the Professor. Any time the military has an operation that can't fail, they call this guy in to train the troops, OK? He's the kind of guy that would drink a gallon of gasoline so he could piss in your campfire You could drop this guy off at the Arctic Circle wearing a pair of bikini underwear, without his toothbrush, and tomorrow afternoon he's going to show up at your pool side with a million dollar smile and fist full of pesos. This guy's a professional, you got me? If he reaches this rig, we're all gonna be nothing but a big goddamned hole right in the middle of Alaska. So let's go find him and kill him and get rid of the son of a bitch!"

setwall:
	st		r1, 26	
	st		r1, 26	
	st		r1, 26	
	st		r1, 26	
	st		r1, 26	

livewall:
	live	%42
	live	%42
	live	%42
	live	%42
	live	%42
	and		r11, r11, r11

seterase:
	ld		-30, r12
	ld		-31, r13
	ld		-32, r14
	ld		-33, r15
	ld		-34, r16

jumpnerase:
	zjmp	%:erase

erase:
	st		r12, -258
	st		r13, -259
	st		r14, -260
	st		r15, -261
	st		r16, -262
	st		r12, -263
	st		r13, -264
	st		r14, -265
	st		r15, -266
	st		r16, -267
	st		r12, -268
	st		r13, -269
	st		r14, -270
	st		r15, -271
	st		r16, -272
	st		r12, -273
	st		r13, -274
	st		r14, -275
	st		r15, -276
	st		r16, -277
	st		r12, -278
	st		r13, -279
	st		r14, -280
	st		r15, -281
	st		r16, -282
	st		r12, -283
	st		r13, -284
	st		r14, -285
	st		r15, -286
	st		r16, -287
	st		r12, -288
	st		r13, -289
	st		r14, -290
	st		r15, -291
	st		r16, -292
	st		r12, -293
	st		r13, -294
	st		r14, -295
	st		r15, -296
	st		r16, -297
	st		r12, -298
	st		r13, -299
	st		r14, -300
	st		r15, -301
	st		r16, -302
	st		r12, -303
	st		r13, -304
	st		r14, -305
	st		r15, -306
	st		r16, -307
	and		r11, r11, r11
	live	%42

fjump:
	st		r1, -4
	fork	%-511
	fork	%:attack

jumpnfork:
	ld		%167705600, r9
	st		r9, :fjump
	ld		%167713280, r10
	st		r10, :seterase
	st		r1, 6
	live	%42
	fork	%:erase
	st		r1, 6
	live	%42
	fork	%-13
	st		r1, 6
	live	%42
	and		r11, r11, r11
	zjmp	%-36
	zjmp	%-253

attack:
	st		r1, 6
	live	%42
	fork	%:dupattack
	st		r1, 6
	live	%42
	ld		%4, r4
	ld		%200, r5
	st		r1, 6
	live	%42
	ldi		r3, %-50, r2
	sti		r2, %200, r3
	add		r3, r4, r3
	and		r11, r11, r11
	zjmp	%-27

dupattack:
	st		r1, 6
	live	%42
	fork	%174
