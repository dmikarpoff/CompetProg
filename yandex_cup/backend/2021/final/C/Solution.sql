SELECT case
	   	 WHEN artist_id is NULL THEN year_
         ELSE NULL
	   END year, 
       artist_id, IFNULL(duration, 0) as duration, IFNULL(plays, 0) as plays, 
	   IFNULL(skips, 0) as skips, IFNULL(likes, 0) as likes, IFNULL(dislikes, 0) as dislikes FROM
(
      SELECT P.year as year_, P.artist_id, duration, plays, skips, likes, dislikes FROM
    	(	
          (SELECT year, artist.id as artist_id FROM artist CROSS JOIN 
    			(SELECT DISTINCT strftime("%Y", event_date) as year from user_history)
    		ORDER BY year) 
           AS P
        ) 
        LEFT JOIN
		(
          (SELECT year, artist_id, SUM(duration) as duration, COUNT(*) AS plays 
             FROM (
               SELECT strftime("%Y", user_history.event_date) as year, 
                      track.duration as duration, event_type.name as event_name, track.id AS track_id,
                      track_artist.artist_id as artist_id
               FROM user_history JOIN event_type ON event_type.id = user_history.event_type_id JOIN
    	            track ON track.id = user_history.track_id JOIN track_artist ON user_history.track_id = track_artist.track_id
             )
    	   WHERE event_name = "play" GROUP by year, artist_id)
        ) USING (year, artist_id)
        LEFT JOIN
        (
          SELECT year, artist_id, COUNT(*) AS skips FROM 
          (    
            SELECT strftime("%Y", user_history.event_date) as year, 
                   track.duration as duration, event_type.name as event_name, track.id AS track_id,
                   track_artist.artist_id as artist_id
             FROM user_history JOIN event_type ON event_type.id = user_history.event_type_id JOIN
    	          track ON track.id = user_history.track_id JOIN track_artist ON user_history.track_id = track_artist.track_id
          )
    	  WHERE event_name = "skip" GROUP by year, artist_id
        ) USING (year, artist_id) 
        LEFT JOIN
        (
          SELECT year, artist_id, COUNT(*) AS likes FROM
          (
            SELECT strftime("%Y", user_history.event_date) as year, 
                   track.duration as duration, event_type.name as event_name, track.id AS track_id,
                   track_artist.artist_id as artist_id
            FROM user_history JOIN event_type ON event_type.id = user_history.event_type_id JOIN
    	         track ON track.id = user_history.track_id JOIN track_artist ON user_history.track_id = track_artist.track_id
          )
    	  WHERE event_name = "like" GROUP by year, artist_id
        ) USING (year, artist_id)
        LEFT JOIN
        (
          SELECT year, artist_id, COUNT(*) AS dislikes FROM
          (
            SELECT strftime("%Y", user_history.event_date) as year, 
                   track.duration as duration, event_type.name as event_name, track.id AS track_id,
                   track_artist.artist_id as artist_id
             FROM user_history JOIN event_type ON event_type.id = user_history.event_type_id JOIN
    	          track ON track.id = user_history.track_id JOIN track_artist ON user_history.track_id = track_artist.track_id
          )
    	  WHERE event_name = "dislike" GROUP by year, artist_id
        ) USING (year, artist_id)
    UNION
		SELECT Y.year as year_, NULL as artist_id, duration, plays, skips, likes, dislikes
    	FROM (SELECT DISTINCT strftime("%Y", event_date) as year from user_history) AS Y 
          LEFT JOIN
    	  (
            SELECT year, SUM(duration) AS duration, COUNT(*) as plays 
            FROM
            (
              SELECT strftime("%Y", user_history.event_date) as year, track.duration as duration, 
                     event_type.name as event_name, track.id AS track_id
              FROM user_history JOIN event_type ON event_type.id = user_history.event_type_id JOIN
    	           track ON track.id = user_history.track_id
            )
            WHERE event_name="play" GROUP by year
          ) USING(year)
          LEFT JOIn
          (
            SELECT year, COUNT(*) AS skips FROM
            (
              SELECT strftime("%Y", user_history.event_date) as year, track.duration as duration, event_type.name as event_name,
    	             track.id AS track_id
              FROM user_history JOIN event_type ON event_type.id = user_history.event_type_id JOIN
    	           track ON track.id = user_history.track_id
            )
            WHERE event_name="skip" GROUP by year
          ) USING(year)
          LEFT JOIN
          (
            SELECT year, COUNT(*) as likes FROM
            (
              SELECT strftime("%Y", user_history.event_date) as year, track.duration as duration, event_type.name as event_name,
    	             track.id AS track_id
              FROM user_history JOIN event_type ON event_type.id = user_history.event_type_id JOIN
    	           track ON track.id = user_history.track_id
            )
            WHERE event_name="like" GROUP by year
          ) Using(year)
          LEFT JOIN
          (SELECT year, COUNT(*) as dislikes FROM
           (
             SELECT strftime("%Y", user_history.event_date) as year, track.duration as duration, event_type.name as event_name,
    	            track.id AS track_id
             FROM user_history JOIN event_type ON event_type.id = user_history.event_type_id JOIN
    	          track ON track.id = user_history.track_id
           )
           WHERE event_name="dislike" GROUP by year
          ) USING(year)
)	
WHERE plays > 0 or skips > 0 or likes > 0 or dislikes > 0;