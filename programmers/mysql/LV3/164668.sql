SELECT B.USER_ID, B.NICKNAME, SUM(PRICE) AS TOTAL_SALE
FROM USED_GOODS_BOARD AS A
JOIN USED_GOODS_USER AS B
ON A.WRITER_ID = B.USER_ID
WHERE STATUS = "DONE"
GROUP BY A.WRITER_ID
HAVING TOTAL_SALE >= 700000
ORDER BY TOTAL_SALE