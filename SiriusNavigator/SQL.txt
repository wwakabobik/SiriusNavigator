// --------- SONG ---------------------------------------- //

// SONG

CREATE TABLE song (
id INT ( 32 ) NOT NULL AUTO_INCREMENT,
artist VARCHAR ( 40 ) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
song VARCHAR ( 40 ) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
album VARCHAR ( 40 ) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
year INT ( 4 ),
genre ENUM ('blues','classic rock','country','dance','disco','funk','grunge', 
'hip- hop','jazz','metal','new age','oldies','other','pop','r&b', 
'rap','reggae','rock','techno','industrial','alternative','ska', 
'death metal','pranks','soundtrack','euro-techno','ambient', 
'trip-hop','vocal','jazz+funk','fusion','trance','classical', 
'instrumental','acid','house','game','sound clip','gospel','noise', 
'alternative rock','bass','punk','space','meditative','instrumental pop', 
'instrumental rock','ethnic','gothic','darkwave','techno-industrial','electronic', 
'pop-folk','eurodance','dream','southern rock','comedy','cult','gangsta', 
'top 40','christian rap','pop/funk','jungle','native us','cabaret','new wave', 
'psychadelic','rave','showtunes','trailer','lo-fi','tribal','acid punk', 
'acid jazz','polka','retro','musical','rock & roll','hard rock','folk', 
'folk-rock','national folk','swing','fast fusion','bebob','latin','revival', 
'celtic','bluegrass','avantgarde','gothic rock','progressive rock', 
'psychedelic rock','symphonic rock','slow rock','big band','chorus', 
'easy listening','acoustic','humour','speech','chanson','opera', 
'chamber music','sonata','symphony','booty bass','primus','porn groove', 
'satire','slow jam','club','tango','samba','folklore','ballad', 
'power ballad','rhytmic soul','freestyle','duet','punk rock','drum solo', 
'acapella','euro-house','dance hall','goa','drum & bass','club-house', 
'hardcore','terror','indie','britpop','negerpunk','polsk punk','beat', 
'christian gangsta','heavy metal','black metal','crossover','contemporary c', 
'christian rock','merengue','salsa','thrash metal','anime','jpop','synthpop'),
source TEXT  CHARACTER SET utf8 COLLATE utf8_general_ci,
time TIME,
lyric TEXT  CHARACTER SET utf8 COLLATE utf8_general_ci,
comment VARCHAR( 40 )  CHARACTER SET utf8 COLLATE utf8_general_ci,
full_data VARCHAR ( 1 ) CHARACTER SET utf8 COLLATE utf8_general_ci,
PRIMARY KEY ( id )
);


INSERT INTO song
  (id, artist, song, album, year, genre, source, time, lyric, comment, full_data)
VALUES
  (:id, :artist, :song, :album, :year, :genre, :source, :time, :lyric, :comment, :full_data)

UPDATE song
SET
  id = :id, artist = :artist, song = :song, album = :album, year = :year, genre = :genre, source = :source, time = :time, lyric = :lyric, comment = :comment, full_data = :full_data
WHERE
  id = :Old_id

DELETE FROM song
WHERE
  id = :Old_id

SELECT song.id, song.artist, song.song, song.album, song.year, song.genre, song.source, song.time, song.lyric, song.comment, song.full_data FROM song
WHERE
  song.id = :id




// ----------- ALBUM ----------------------------------------------


// ALBUM

CREATE TABLE album (
id INT ( 32 ) NOT NULL AUTO_INCREMENT,
artist VARCHAR ( 40 ) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
album VARCHAR ( 40 ) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
year INT ( 4 ),
genre ENUM ('blues','classic rock','country','dance','disco','funk','grunge', 
'hip- hop','jazz','metal','new age','oldies','other','pop','r&b', 
'rap','reggae','rock','techno','industrial','alternative','ska', 
'death metal','pranks','soundtrack','euro-techno','ambient', 
'trip-hop','vocal','jazz+funk','fusion','trance','classical', 
'instrumental','acid','house','game','sound clip','gospel','noise', 
'alternative rock','bass','punk','space','meditative','instrumental pop', 
'instrumental rock','ethnic','gothic','darkwave','techno-industrial','electronic', 
'pop-folk','eurodance','dream','southern rock','comedy','cult','gangsta', 
'top 40','christian rap','pop/funk','jungle','native us','cabaret','new wave', 
'psychadelic','rave','showtunes','trailer','lo-fi','tribal','acid punk', 
'acid jazz','polka','retro','musical','rock & roll','hard rock','folk', 
'folk-rock','national folk','swing','fast fusion','bebob','latin','revival', 
'celtic','bluegrass','avantgarde','gothic rock','progressive rock', 
'psychedelic rock','symphonic rock','slow rock','big band','chorus', 
'easy listening','acoustic','humour','speech','chanson','opera', 
'chamber music','sonata','symphony','booty bass','primus','porn groove', 
'satire','slow jam','club','tango','samba','folklore','ballad', 
'power ballad','rhytmic soul','freestyle','duet','punk rock','drum solo', 
'acapella','euro-house','dance hall','goa','drum & bass','club-house', 
'hardcore','terror','indie','britpop','negerpunk','polsk punk','beat', 
'christian gangsta','heavy metal','black metal','crossover','contemporary c', 
'christian rock','merengue','salsa','thrash metal','anime','jpop','synthpop'),
source TEXT CHARACTER SET utf8 COLLATE utf8_general_ci,
comment TEXT CHARACTER SET utf8 COLLATE utf8_general_ci,
cover LONGBLOB,
PRIMARY KEY ( id )
);



INSERT INTO album
  (id, artist, album, year, genre, source, comment, cover)
VALUES
  (:id, :artist, :album, :year, :genre, :source, :comment, :cover)




UPDATE album
SET
  id = :id, artist = :artist, album = :album, year = :year, genre = :genre, source = :source, comment = :comment, cover = :cover
WHERE
  id = :Old_id



DELETE FROM album
WHERE
  id = :Old_id


SELECT album.id, album.artist, album.album, album.year, album.genre, album.source, album.comment, album.cover FROM album
WHERE
  album.id = :id


// ------ ARTIST ----------------------------------------------------


// ARTIST

CREATE TABLE artist (
id INT ( 32 ) NOT NULL AUTO_INCREMENT,
artist VARCHAR ( 40 ) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
genre ENUM ('blues','classic rock','country','dance','disco','funk','grunge', 
'hip- hop','jazz','metal','new age','oldies','other','pop','r&b', 
'rap','reggae','rock','techno','industrial','alternative','ska', 
'death metal','pranks','soundtrack','euro-techno','ambient', 
'trip-hop','vocal','jazz+funk','fusion','trance','classical', 
'instrumental','acid','house','game','sound clip','gospel','noise', 
'alternative rock','bass','punk','space','meditative','instrumental pop', 
'instrumental rock','ethnic','gothic','darkwave','techno-industrial','electronic', 
'pop-folk','eurodance','dream','southern rock','comedy','cult','gangsta', 
'top 40','christian rap','pop/funk','jungle','native us','cabaret','new wave', 
'psychadelic','rave','showtunes','trailer','lo-fi','tribal','acid punk', 
'acid jazz','polka','retro','musical','rock & roll','hard rock','folk', 
'folk-rock','national folk','swing','fast fusion','bebob','latin','revival', 
'celtic','bluegrass','avantgarde','gothic rock','progressive rock', 
'psychedelic rock','symphonic rock','slow rock','big band','chorus', 
'easy listening','acoustic','humour','speech','chanson','opera', 
'chamber music','sonata','symphony','booty bass','primus','porn groove', 
'satire','slow jam','club','tango','samba','folklore','ballad', 
'power ballad','rhytmic soul','freestyle','duet','punk rock','drum solo', 
'acapella','euro-house','dance hall','goa','drum & bass','club-house', 
'hardcore','terror','indie','britpop','negerpunk','polsk punk','beat', 
'christian gangsta','heavy metal','black metal','crossover','contemporary c', 
'christian rock','merengue','salsa','thrash metal','anime','jpop','synthpop'),
source TEXT CHARACTER SET utf8 COLLATE utf8_general_ci,
comment TEXT  CHARACTER SET utf8 COLLATE utf8_general_ci,
picture LONGBLOB,
PRIMARY KEY ( id )
);


INSERT INTO artist
  (id, artist, genre, source, comment, picture)
VALUES
  (:id, :artist, :genre, :source, :comment, :picture)


UPDATE artist
SET
  id = :id, artist = :artist, genre = :genre, source = :source, comment = :comment, picture = :picture
WHERE
  id = :Old_id


DELETE FROM artist
WHERE
  id = :Old_id



SELECT artist.id, artist.artist, artist.genre, artist.source, artist.comment, artist.picture FROM artist
WHERE
  artist.id = :id


// -------------- TRIGGERS ----------------------------------------- //


CREATE TRIGGER artist_genre AFTER UPDATE ON artist
FOR EACH ROW
LANGUAGE SQL
BEGIN
UPDATE album SET  album.genre = NEW.genre WHERE NEW.artist=album.artist;
END

CREATE TRIGGER album_genre AFTER UPDATE ON album
FOR EACH ROW
LANGUAGE SQL
BEGIN
UPDATE song SET song.genre = NEW.genre WHERE (NEW.album=song.album AND NEW.artist=song.artist);
END


// --------------- PROCEDURES-------------------------- //

// ******* INSERT *********

//SONG - ALBUM

CREATE PROCEDURE insert_song_album ()
LANGUAGE SQL
BEGIN

/* End flag */
DECLARE is_end INT DEFAULT 0;

/* Buffer Variables */
DECLARE buf_artist VARCHAR ( 40 );
DECLARE buf_album VARCHAR ( 40 );
DECLARE buf_year INT ( 4 );

/* Cursor Definition */
DECLARE son_alb CURSOR FOR 
Select song.artist, song.album, song.year from song
left outer join album on album.album=song.album
where album.album is null GROUP BY song.album;

/* Error condition */
DECLARE CONTINUE HANDLER FOR NOT FOUND SET is_end = 1;

/* Procedure*/
OPEN son_alb;

wet : LOOP
FETCH son_alb INTO buf_artist, buf_album, buf_year;
IF is_end THEN LEAVE wet;
END IF;
INSERT INTO album
  (artist, album, year)
VALUES (buf_artist, buf_album, buf_year);
END LOOP wet;
CLOSE son_alb;

END

// SONG - ARTIST

CREATE PROCEDURE insert_song_artist ()
LANGUAGE SQL
BEGIN

/* End flag */
DECLARE is_end INT DEFAULT 0;

/* Buffer Variables */
DECLARE buf_artist VARCHAR ( 40 );

/* Cursor Definition */
DECLARE son_art CURSOR FOR 
Select song.artist from song
left outer join artist on artist.artist=song.artist
where artist.artist is null GROUP BY song.artist;

/* Error condition */
DECLARE CONTINUE HANDLER FOR NOT FOUND SET is_end = 1;

/* Procedure*/
OPEN son_art;

wet : LOOP
FETCH son_art INTO buf_artist;
IF is_end THEN LEAVE wet;
END IF;
INSERT INTO artist
  (artist)
VALUES (buf_artist);
END LOOP wet;
CLOSE son_art;

END

// ALBUM - ARTIST

CREATE PROCEDURE insert_album_artist ()
LANGUAGE SQL
BEGIN

/* End flag */
DECLARE is_end INT DEFAULT 0;

/* Buffer Variables */
DECLARE buf_artist VARCHAR ( 40 );

/* Cursor Definition */
DECLARE alb_art CURSOR FOR 
Select album.artist from album
left outer join artist on artist.artist=album.artist
where artist.artist is null GROUP BY album.artist;

/* Error condition */
DECLARE CONTINUE HANDLER FOR NOT FOUND SET is_end = 1;

/* Procedure*/
OPEN alb_art;

wet : LOOP
FETCH alb_art INTO buf_artist;
IF is_end THEN LEAVE wet;
END IF;
INSERT INTO artist
  (artist)
VALUES (buf_artist);
END LOOP wet;
CLOSE alb_art;

END

// ********* DELETE ****************

// ON ALBUM

CREATE PROCEDURE delete_empty_album ()
LANGUAGE SQL
BEGIN

/* End flag */
DECLARE is_end INT DEFAULT 0;

/* Buffer Variables */
DECLARE buf_id INT ( 32 );

/* Cursor Definition */
DECLARE del_alb CURSOR FOR 
select album.id from album
where NOT EXISTS (select * from song where song.album=album.album);

/* Error condition */
DECLARE CONTINUE HANDLER FOR NOT FOUND SET is_end = 1;

/* Procedure*/
OPEN del_alb;

wet : LOOP
FETCH del_alb INTO buf_id;
IF is_end THEN LEAVE wet;
END IF;
DELETE FROM album
WHERE
  id = buf_id;
END LOOP wet;
CLOSE del_alb;

END

// ON ARTIST

CREATE PROCEDURE delete_empty_artist ()
BEGIN

/* End flag */
DECLARE is_end INT DEFAULT 0;

/* Buffer Variables */
DECLARE buf_id INT ( 32 );

/* Cursor Definition */
DECLARE del_art CURSOR FOR 
select artist.id from artist
where NOT EXISTS (select * from song where song.artist=artist.artist);

/* Error condition */
DECLARE CONTINUE HANDLER FOR NOT FOUND SET is_end = 1;

/* Procedure*/
OPEN del_art;

wet : LOOP
FETCH del_art INTO buf_id;
IF is_end THEN LEAVE wet;
END IF;
DELETE FROM artist
WHERE
  id = buf_id;
END LOOP wet;
CLOSE del_art;

END


/* ------------------ DELDUPE ----------------------- */

// ON ARTIST

CREATE PROCEDURE delete_artist_dupe ()
LANGUAGE SQL
BEGIN

/* End flag */
DECLARE is_end INT DEFAULT 0;

/* Buffer Variables */
DECLARE buf_id INT ( 32 );
DECLARE inc INT ( 32 ) DEFAULT 0;
DECLARE buf_artist VARCHAR ( 40 );
DECLARE buf_artist2 VARCHAR ( 40 );

/* Cursor Definition */
DECLARE del_art_cur CURSOR FOR 
select artist.id, artist.artist from artist, artist as phantom where (artist.artist=phantom.artist AND artist.id <> phantom.id) GROUP BY artist.id ORDER BY artist.artist;

/* Error condition */
DECLARE CONTINUE HANDLER FOR NOT FOUND SET is_end = 1;

/* Procedure*/
OPEN del_art_cur;

wet : LOOP
SET inc = inc + 1;
FETCH del_art_cur INTO buf_id, buf_artist;
IF is_end THEN 
LEAVE wet;
END IF;
IF buf_artist=buf_artist2 AND inc <> 1
THEN 
DELETE FROM artist
WHERE
  id = buf_id;
ELSEIF inc = 1 
THEN SET buf_artist2=buf_artist;
ELSE SET buf_artist2=buf_artist;
END IF;
END LOOP wet;
CLOSE del_art_cur;

END


// ON ALBUM

CREATE PROCEDURE delete_album_dupe (flag INT)
LANGUAGE SQL
BEGIN

/* End flag */
DECLARE is_end INT DEFAULT 0;

/* Buffer Variables */
DECLARE buf_id INT ( 32 );
DECLARE inc INT ( 32 ) DEFAULT 0;
DECLARE buf_album VARCHAR ( 40 );
DECLARE buf_album2 VARCHAR ( 40 );

/* Cursor Definition */
/* WITh YEAR */
DECLARE del_alb_cur CURSOR FOR 
select album.id, album.album from album, album as phantom where (album.artist=phantom.artist AND album.album=phantom.album AND album.year=phantom.year AND album.id <> phantom.id)  GROUP BY album.id ORDER BY album.album;
/* WITHOUT YEAR */
DECLARE del_alb_cur1 CURSOR FOR 
select album.id, album.album from album, album as phantom where (album.artist=phantom.artist AND album.album=phantom.album AND album.id <> phantom.id) GROUP BY album.id ORDER BY album.album;

/* Error condition */
DECLARE CONTINUE HANDLER FOR NOT FOUND SET is_end = 1;

/* Procedure*/

CASE flag

/* WITH YEAR */

WHEN 0 THEN
OPEN del_alb_cur;
wet : LOOP
SET inc = inc + 1;
FETCH del_alb_cur INTO buf_id, buf_album;
IF is_end THEN 
LEAVE wet;
END IF;
IF buf_album=buf_album2 AND inc <> 1
THEN 
DELETE FROM album
WHERE
  id = buf_id;
ELSEIF inc = 1 
THEN SET buf_album2=buf_album;
ELSE SET buf_album2=buf_album;
END IF;
END LOOP wet;
CLOSE del_alb_cur;

/* WITHOUT YEAR */


WHEN 1 THEN
OPEN del_alb_cur1;
wet : LOOP
SET inc = inc + 1;
FETCH del_alb_cur1 INTO buf_id, buf_album;
IF is_end THEN 
LEAVE wet;
END IF;
IF buf_album=buf_album2 AND inc <> 1
THEN 
DELETE FROM album
WHERE
  id = buf_id;
ELSEIF inc = 1 
THEN SET buf_album2=buf_album;
ELSE SET buf_album2=buf_album;
END IF;
END LOOP wet;
CLOSE del_alb_cur1;

END CASE;


END


// ON SONG

CREATE PROCEDURE delete_song_dupe (flag INT)
LANGUAGE SQL

BEGIN

/* End flag */
DECLARE is_end INT DEFAULT 0;

/* Buffer Variables */
DECLARE buf_id INT ( 32 );
DECLARE inc INT ( 32 ) DEFAULT 0;
DECLARE buf_song VARCHAR ( 40 );
DECLARE buf_song2 VARCHAR ( 40 );

/* Cursor Definition */

/* FULL */
DECLARE del_son_cur CURSOR FOR 
select song.id, song.song from song, song as phantom where (song.artist=phantom.artist AND song.album=phantom.album AND song.year=phantom.year AND song.song=phantom.song AND song.id <> phantom.id) GROUP BY song.id ORDER BY song.song;

/* FULL EXPANDED WITH TIME */
DECLARE del_son_cur1 CURSOR FOR 
select song.id, song.song from song, song as phantom where (song.artist=phantom.artist AND song.album=phantom.album AND song.year=phantom.year AND song.song=phantom.song AND song.time=phantom.time AND song.id <> phantom.id)  GROUP BY song.id ORDER BY song.song;

/* FULL - EXPANDED WITH TIME (FULL) (WITH FilePath) */
DECLARE del_son_cur2 CURSOR FOR 
select song.id, song.song from song, song as phantom where (song.artist=phantom.artist AND song.album=phantom.album AND song.year=phantom.year AND song.song=phantom.song AND song.time=phantom.time AND song.source=phantom.source AND song.id <> phantom.id)  GROUP BY song.id ORDER BY song.song;

/* FULL - WITHOUT TIME (WITH FilePath) */
DECLARE del_son_cur3 CURSOR FOR 
select song.id, song.song  from song, song as phantom where (song.artist=phantom.artist AND song.album=phantom.album AND song.year=phantom.year AND song.song=phantom.song AND song.source=phantom.source AND song.id <> phantom.id)  GROUP BY song.id ORDER BY song.song;

/* WITHOUT YEAR */
DECLARE del_son_cur4 CURSOR FOR 
select song.id, song.song from song, song as phantom where (song.artist=phantom.artist AND song.album=phantom.album AND song.song=phantom.song AND song.id <> phantom.id)  GROUP BY song.id ORDER BY song.song;

/* WITHOUT ALBUM */
DECLARE del_son_cur5 CURSOR FOR 
select song.id, song.song from album, song as phantom where (song.artist=phantom.artist AND song.song=phantom.song AND song.id <> phantom.id)  GROUP BY song.id ORDER BY song.song;

/* Error condition */
DECLARE CONTINUE HANDLER FOR NOT FOUND SET is_end = 1;

/* Procedure*/

CASE flag

/* FULL */

WHEN 0 THEN

OPEN del_son_cur;
wet : LOOP
SET inc = inc + 1;
FETCH del_son_cur INTO buf_id, buf_song;
IF is_end THEN 
LEAVE wet;
END IF;
IF buf_song=buf_song2 AND inc <> 1
THEN 
DELETE FROM song
WHERE
  id = buf_id;
ELSEIF inc = 1 
THEN SET buf_song2=buf_song;
ELSE SET buf_song2=buf_song;
END IF;
END LOOP wet;
CLOSE del_son_cur;

/* FULL EXPANDED WITH TIME */

WHEN 1 THEN

OPEN del_son_cur1;
wet : LOOP
SET inc = inc + 1;
FETCH del_son_cur1 INTO buf_id, buf_song;
IF is_end THEN 
LEAVE wet;
END IF;
IF buf_song=buf_song2 AND inc <> 1
THEN 
DELETE FROM song
WHERE
  id = buf_id;
ELSEIF inc = 1 
THEN SET buf_song2=buf_song;
ELSE SET buf_song2=buf_song;
END IF;
END LOOP wet;
CLOSE del_son_cur1;

/* FULL - EXPANDED WITH TIME (FULL) (WITH FilePath) */

WHEN 2 THEN

OPEN del_son_cur2;
wet : LOOP
SET inc = inc + 1;
FETCH del_son_cur2 INTO buf_id, buf_song;
IF is_end THEN 
LEAVE wet;
END IF;
IF buf_song=buf_song2 AND inc <> 1
THEN 
DELETE FROM song
WHERE
  id = buf_id;
ELSEIF inc = 1 
THEN SET buf_song2=buf_song;
ELSE SET buf_song2=buf_song;
END IF;
END LOOP wet;
CLOSE del_son_cur2;


/* FULL - WITHOUT TIME (WITH FilePath) */

WHEN 3 THEN

OPEN del_son_cur3;
wet : LOOP
SET inc = inc + 1;
FETCH del_son_cur3 INTO buf_id, buf_song;
IF is_end THEN 
LEAVE wet;
END IF;
IF buf_song=buf_song2 AND inc <> 1
THEN 
DELETE FROM song
WHERE
  id = buf_id;
ELSEIF inc = 1 
THEN SET buf_song2=buf_song;
ELSE SET buf_song2=buf_song;
END IF;
END LOOP wet;
CLOSE del_son_cur3;


/* WITHOUT YEAR */

WHEN 4 THEN

OPEN del_son_cur4;
wet : LOOP
SET inc = inc + 1;
FETCH del_son_cur4 INTO buf_id, buf_song;
IF is_end THEN 
LEAVE wet;
END IF;
IF buf_song=buf_song2 AND inc <> 1
THEN 
DELETE FROM song
WHERE
  id = buf_id;
ELSEIF inc = 1 
THEN SET buf_song2=buf_song;
ELSE SET buf_song2=buf_song;
END IF;
END LOOP wet;
CLOSE del_son_cur4;

/* WITHOUT ALBUM */

WHEN 5 THEN

OPEN del_son_cur5;
wet : LOOP
SET inc = inc + 1;
FETCH del_son_cur5 INTO buf_id, buf_song;
IF is_end THEN 
LEAVE wet;
END IF;
IF buf_song=buf_song2 AND inc <> 1
THEN 
DELETE FROM song
WHERE
  id = buf_id;
ELSEIF inc = 1 
THEN SET buf_song2=buf_song;
ELSE SET buf_song2=buf_song;
END IF;
END LOOP wet;
CLOSE del_son_cur5;

END CASE;

END



// ----------------- VIEWS -------------------------------- //

CREATE OR REPLACE VIEW user_cut_songs AS
SELECT song, artist, album, year, time FROM song ORDER BY genre, artist, year, album, song ASC;

CREATE OR REPLACE VIEW user_cut_albums AS
SELECT artist, album, year, (select count(id) from song WHERE song.album=album.album) AS total FROM album ORDER BY genre, artist, year, album ASC;

CREATE OR REPLACE VIEW user_cut_albums_full AS
SELECT artist, album, year, (select count(id) from song WHERE song.album=album.album) AS total, cover FROM album ORDER BY genre, artist, year, album ASC;

CREATE OR REPLACE VIEW user_cut_artist AS
SELECT artist, (select count(id) from song WHERE song.artist=artist.artist) AS songs, (select count(id) from album WHERE album.artist=artist.artist) AS albums FROM artist ORDER BY genre, artist, albums, songs ASC;

CREATE OR REPLACE VIEW user_cut_artist_full AS
SELECT artist, (select count(id) from song WHERE song.artist=artist.artist) AS songs, (select count(id) from album WHERE album.artist=artist.artist) AS albums, picture FROM artist ORDER BY genre, artist, albums, songs ASC;


// ---------------- FUNCTIONS --------------------------------- //


CREATE FUNCTION return_time (param VARCHAR ( 40 ), flag INT, flag2 INT)
RETURNS CHARACTER ( 40 )
LANGUAGE SQL
BEGIN
DECLARE retstring CHARACTER ( 40 );
DECLARE sectime INT DEFAULT 0;
DECLARE days INT DEFAULT 0;
DECLARE hours INT DEFAULT 0;
DECLARE minutes INT DEFAULT 0;
DECLARE seconds INT DEFAULT 0;

CASE flag
WHEN 0 THEN
select sum(time) AS sum_time into sectime from song;
WHEN 1 THEN
select sum(time) AS sum_time into sectime from song WHERE album LIKE CONCAT("%",param,"%");
WHEN 2 THEN
select sum(time) AS sum_time into sectime from song WHERE artist LIKE CONCAT("%",param,"%");
WHEN 3 THEN
select sum(time) AS sum_time into sectime from song WHERE genre LIKE CONCAT("%",param,"%");
END CASE;

SET days = FLOOR(sectime/86400);
SET seconds = sectime-days*86400;
SET hours = FLOOR(seconds/3600);
SET seconds = seconds-hours*3600;
SET minutes = FLOOR(seconds/60);
SET seconds = seconds-minutes*60;

CASE flag2
WHEN 1 THEN
SET retstring = CONCAT(days, ":", hours, ":", minutes, ":", seconds);
WHEN 0 THEN
SET retstring = CONCAT(days, " days ", hours, " hours ", minutes, " minutes ", seconds, " seconds" );
WHEN 3 THEN
SET retstring = CONCAT(hours, " hours ", minutes, " minutes ", seconds, " seconds" );
END CASE;
RETURN retstring;
END




/* ------------ PRINT HTML ------------------------ */



CREATE PROCEDURE html_print (param VARCHAR ( 40 ), number INT)
LANGUAGE SQL
BEGIN

/* End flag */
DECLARE is_end INT DEFAULT 0;

/* Buffer Variables */
DECLARE buf_song VARCHAR ( 40 );
DECLARE buf_artist VARCHAR ( 40 );
DECLARE buf_album VARCHAR ( 40 );
DECLARE buf_album2 VARCHAR ( 40 );
DECLARE buf_year INT ( 4 );
DECLARE buf_time TIME;
DECLARE my_html LONGTEXT;
DECLARE temp_time VARCHAR( 40 );
DECLARE inc INT ( 4 ) DEFAULT 0;
DECLARE number2 INT ( 4 ) DEFAULT 0;
/* Cursor Definition */
DECLARE song_html CURSOR FOR 
Select song, artist, album, year, time from song where artist = param ORDER BY artist, year, album, song; 

/* Error condition */
DECLARE CONTINUE HANDLER FOR NOT FOUND SET is_end = 1;

/* Procedure*/
SET my_html = Concat("<HTML><HEAD><TITLE>Sirius DB - ", param,"</TITLE></HEAD><BODY>");

OPEN song_html;

wet : LOOP

FETCH song_html INTO buf_song, buf_artist, buf_album, buf_year, buf_time;
IF buf_year <=> NULL THEN
SET buf_year = 0;
END IF;
IF buf_album <=> NULL THEN
SET buf_album = 'misc';
END IF;

IF is_end THEN LEAVE wet;
END IF;

IF inc = 0 THEN
SET buf_album2=buf_album;
END IF;

IF buf_album2 <> buf_album OR inc=0 THEN
   IF inc <> 0 THEN
   Select return_time(buf_album2,1,3) AS tt into temp_time; 
   SET my_html = CONCAT(my_html, "<BR><b><i>", temp_time, "</b></i>" );
   END IF;
SET buf_album2=buf_album;
SET number2 = number2+1;
SET my_html = CONCAT(my_html,"<BR><HR><IMG src='ALBUMS/",number,"_",number2,".jpg' allign='center'><H1><b>",buf_album," (",buf_year,")</b></H1><BR>");
SET inc = 0;
END IF;

SET inc = inc+1;
SET my_html = CONCAT(my_html,"<BR>",inc,". ",buf_artist," - ",buf_song," (", MINUTE(buf_time),":",SECOND(buf_time), ") <a href='LYRICS/",number,"_",number2,"_",inc,".html'>L</a>");
END LOOP wet;

CLOSE song_html;

Select return_time(buf_album2,1,3) AS tt into temp_time; 
SET my_html = CONCAT(my_html, "<BR><b><i>", temp_time, "</b></i>" );


Select return_time(buf_artist,2,3) AS tt into temp_time; 
SET my_html = CONCAT(my_html, "<HR><BR><b><i>", temp_time, "</b></i>" );

SET my_html=CONCAT(my_html,"</BODY></HTML>");
Select my_html AS HTML;
END