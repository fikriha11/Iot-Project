import React from "react";

function Datetime({ dateString }) {
  var dateObj = new Date(dateString);
  var year = dateObj.getFullYear();
  var month = dateObj.getMonth();
  var date = dateObj.getDate();
  var hours = dateObj.getHours();
  var minutes = dateObj.getMinutes();

  var months = [
    "Jan",
    "Feb",
    "Mar",
    "Apr",
    "May",
    "Jun",
    "Jul",
    "Aug",
    "Sept",
    "Octo",
    "Nov",
    "Des",
  ];

  return (
    <div>
      <hr className="my-4" />
      <p className="text-muted mb-1">Last update:</p>
      <p className="text-muted">
        {hours}:{minutes}, {date} {months[month]} {year}
      </p>
    </div>
  );
}

export default Datetime;
