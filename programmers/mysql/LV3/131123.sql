SELECT A.FOOD_TYPE, A.REST_ID, A.REST_NAME, A.FAVORITES
FROM REST_INFO AS A
JOIN (SELECT FOOD_TYPE, MAX(FAVORITES) AS MAX_FAVORITES
        FROM REST_INFO
        GROUP BY FOOD_TYPE) AS B
ON A.FOOD_TYPE = B.FOOD_TYPE
WHERE A.FAVORITES = B.MAX_FAVORITES
# GROUP BY A.FOOD_TYPE
ORDER BY A.FOOD_TYPE DESC