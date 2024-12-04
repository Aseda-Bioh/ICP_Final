-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Dec 04, 2024 at 10:29 PM
-- Server version: 10.4.32-MariaDB
-- PHP Version: 8.2.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `university_system`
--

-- --------------------------------------------------------

--
-- Table structure for table `academic_program`
--

CREATE TABLE `academic_program` (
  `id` int(11) NOT NULL,
  `programCode` varchar(10) NOT NULL,
  `programName` varchar(100) NOT NULL,
  `departmentCode` varchar(10) NOT NULL,
  `degreeLevel` enum('UNDERGRADUATE','GRADUATE','DOCTORAL') NOT NULL,
  `creditRequirement` int(11) NOT NULL,
  `dateCreated` datetime DEFAULT current_timestamp(),
  `isActive` tinyint(1) DEFAULT 1
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `academic_program`
--

INSERT INTO `academic_program` (`id`, `programCode`, `programName`, `departmentCode`, `degreeLevel`, `creditRequirement`, `dateCreated`, `isActive`) VALUES
(1, 'CS', 'New Program Name', 'CSE', 'UNDERGRADUATE', 120, '2024-12-02 21:06:23', 0),
(2, 'MIS', 'Management Information Systems', 'CSE', 'UNDERGRADUATE', 120, '2024-12-02 21:06:23', 1),
(3, 'BA', 'Business Administration', 'BUS', 'UNDERGRADUATE', 120, '2024-12-02 21:06:23', 1),
(4, 'ME', 'Mechanical Engineering', 'ENG', 'UNDERGRADUATE', 130, '2024-12-02 21:06:23', 1),
(5, 'EE', 'Electrical Engineering', 'ENG', 'UNDERGRADUATE', 130, '2024-12-02 21:06:23', 1),
(6, 'ECON', 'Economics', 'HUM', 'UNDERGRADUATE', 120, '2024-12-02 21:06:23', 1),
(7, 'CE', 'Computer Engineering', 'ENG', 'UNDERGRADUATE', 130, '2024-12-02 21:06:23', 1),
(8, 'LAW', 'Law', 'HUM', 'UNDERGRADUATE', 120, '2024-12-02 21:06:23', 1),
(9, 'MECHATRONI', 'Mechatronics', 'ENG', 'UNDERGRADUATE', 130, '2024-12-02 21:06:23', 1),
(10, 'CS-BSC', 'Bachelor of Science in Computer Science', 'CSE', 'UNDERGRADUATE', 120, '2024-12-03 23:01:18', 1),
(11, 'CS-MSC', 'Master of Science in Computer Science', 'CSE', 'GRADUATE', 36, '2024-12-03 23:01:18', 1),
(12, 'BBA', 'Bachelor of Business Administration', 'BUS', 'UNDERGRADUATE', 120, '2024-12-03 23:01:18', 1),
(13, 'MBA', 'Master of Business Administration', 'BUS', 'GRADUATE', 48, '2024-12-03 23:01:18', 1),
(14, 'ME-BSC', 'Bachelor of Mechanical Engineering', 'ENG', 'UNDERGRADUATE', 130, '2024-12-03 23:01:18', 1),
(15, 'CE-BSC', 'Bachelor of Civil Engineering', 'ENG', 'UNDERGRADUATE', 130, '2024-12-03 23:01:18', 1),
(17, 'DS', 'kllghilghg', 'CSE', 'GRADUATE', 120, '2024-12-03 23:05:30', 0),
(18, 'AI', 'Artificial Intelligence', 'CSE', 'GRADUATE', 36, '2024-12-03 23:05:30', 1),
(19, 'CYB', 'Cybersecurity', 'CSE', 'UNDERGRADUATE', 120, '2024-12-03 23:05:30', 1),
(20, 'SE', 'Software Engineering', 'CSE', 'UNDERGRADUATE', 120, '2024-12-03 23:05:30', 1),
(21, 'WEB', 'Web Technologies', 'CSE', 'UNDERGRADUATE', 36, '2024-12-04 12:22:43', 1),
(22, 'LAFHALGFA', 'adkjfgalifflaf', 'CSE', 'UNDERGRADUATE', 36, '2024-12-04 21:14:55', 1);

-- --------------------------------------------------------

--
-- Table structure for table `academic_term`
--

CREATE TABLE `academic_term` (
  `id` int(11) NOT NULL,
  `termCode` varchar(20) NOT NULL,
  `termName` varchar(50) NOT NULL,
  `startDate` date NOT NULL,
  `endDate` date NOT NULL,
  `isActive` tinyint(1) DEFAULT 1,
  `dateCreated` datetime DEFAULT current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `academic_term`
--

INSERT INTO `academic_term` (`id`, `termCode`, `termName`, `startDate`, `endDate`, `isActive`, `dateCreated`) VALUES
(1, '202401', 'Spring 2024', '2024-01-15', '2024-05-15', 1, '2024-12-03 11:19:13'),
(2, '202402', 'Summer 2024', '2024-06-01', '2024-08-15', 1, '2024-12-03 11:19:13'),
(3, '202403', 'Fall 2024', '2024-09-01', '2024-12-15', 1, '2024-12-03 11:19:13'),
(22, '202310', 'Fall 2023', '2023-09-01', '2023-12-15', 1, '2024-12-04 19:43:54'),
(23, '202320', 'Spring 2023', '2023-01-15', '2023-05-15', 1, '2024-12-04 19:43:54'),
(24, '202330', 'Summer 2023', '2023-06-01', '2023-08-15', 1, '2024-12-04 19:43:54'),
(25, '202410', 'Fall 2024', '2024-09-01', '2024-12-15', 1, '2024-12-04 19:43:54'),
(26, '202420', 'Spring 2024', '2024-01-15', '2024-05-15', 1, '2024-12-04 19:43:54'),
(27, '202430', 'Summer 2024', '2024-06-01', '2024-08-15', 1, '2024-12-04 19:43:54');

-- --------------------------------------------------------

--
-- Stand-in structure for view `active_terms`
-- (See below for the actual view)
--
CREATE TABLE `active_terms` (
`termCode` varchar(20)
,`termDisplay` varchar(73)
);

-- --------------------------------------------------------

--
-- Table structure for table `course`
--

CREATE TABLE `course` (
  `id` int(11) NOT NULL,
  `courseCode` varchar(20) NOT NULL,
  `courseName` varchar(100) NOT NULL,
  `departmentCode` varchar(10) NOT NULL,
  `credits` int(11) NOT NULL,
  `description` text DEFAULT NULL,
  `prerequisites` text DEFAULT NULL,
  `dateCreated` datetime DEFAULT current_timestamp(),
  `lastModified` datetime DEFAULT current_timestamp() ON UPDATE current_timestamp(),
  `isActive` tinyint(1) DEFAULT 1
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `course`
--

INSERT INTO `course` (`id`, `courseCode`, `courseName`, `departmentCode`, `credits`, `description`, `prerequisites`, `dateCreated`, `lastModified`, `isActive`) VALUES
(1, 'CS101', 'Introduction to Programming', 'CSE', 3, 'Basic programming concepts using Python', NULL, '2024-12-03 11:19:13', '2024-12-03 11:19:13', 1),
(2, 'CS201', 'Data Structures', 'CSE', 3, 'Fundamental data structures and algorithms', 'CS101', '2024-12-03 11:19:13', '2024-12-03 11:19:13', 1),
(3, 'CS301', 'Database Systems', 'CSE', 3, 'Database design and SQL', 'CS201', '2024-12-03 11:19:13', '2024-12-03 11:19:13', 1),
(4, 'MATH101', 'Calculus I', 'CSE', 4, 'Introduction to differential calculus', NULL, '2024-12-03 11:19:13', '2024-12-03 11:19:13', 1),
(5, 'BUS101', 'Introduction to Business', 'BUS', 3, 'Basic business concepts', NULL, '2024-12-03 11:19:13', '2024-12-03 11:19:13', 1),
(6, 'ENG101', 'Engineering Principles', 'ENG', 3, 'Basic engineering concepts', NULL, '2024-12-03 11:19:13', '2024-12-03 11:19:13', 1),
(15, 'CS102', 'Object-Oriented Programming', 'CSE', 3, 'Advanced programming concepts using Java', 'CS101', '2024-12-03 13:36:57', '2024-12-03 13:36:57', 1),
(16, 'CS202', 'Algorithms and Complexity', 'CSE', 3, 'Analysis and design of algorithms', 'CS201', '2024-12-03 13:36:57', '2024-12-03 13:36:57', 1),
(17, 'CS303', 'Software Engineering', 'CSE', 3, 'Software development lifecycle and methodologies', 'CS201', '2024-12-03 13:36:57', '2024-12-03 13:36:57', 1),
(18, 'MATH201', 'Calculus II', 'CSE', 4, 'Integral calculus and applications', 'MATH101', '2024-12-03 13:36:57', '2024-12-03 13:36:57', 1),
(19, 'BUS201', 'Financial Accounting', 'BUS', 3, 'Fundamentals of accounting principles', 'BUS101', '2024-12-03 13:36:57', '2024-12-03 13:36:57', 1),
(20, 'ENG201', 'Circuit Theory', 'ENG', 3, 'Basic electrical circuit analysis', 'ENG101', '2024-12-03 13:36:57', '2024-12-03 13:36:57', 1);

-- --------------------------------------------------------

--
-- Table structure for table `course_offering`
--

CREATE TABLE `course_offering` (
  `id` int(11) NOT NULL,
  `courseCode` varchar(20) NOT NULL,
  `termCode` varchar(20) NOT NULL,
  `facultyID` varchar(50) NOT NULL,
  `section` varchar(10) NOT NULL,
  `capacity` int(11) NOT NULL,
  `enrolledCount` int(11) DEFAULT 0,
  `status` enum('SCHEDULED','IN_PROGRESS','COMPLETED','CANCELLED') DEFAULT 'SCHEDULED',
  `dateCreated` datetime DEFAULT current_timestamp(),
  `lastModified` datetime DEFAULT current_timestamp() ON UPDATE current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `course_offering`
--

INSERT INTO `course_offering` (`id`, `courseCode`, `termCode`, `facultyID`, `section`, `capacity`, `enrolledCount`, `status`, `dateCreated`, `lastModified`) VALUES
(1, 'CS101', '202401', 'FAC001', 'A', 30, 1, 'IN_PROGRESS', '2024-12-03 11:19:13', '2024-12-03 13:36:58'),
(2, 'CS101', '202401', 'FAC001', 'B', 30, 0, 'IN_PROGRESS', '2024-12-03 11:19:13', '2024-12-03 13:36:58'),
(3, 'CS201', '202401', 'FAC001', 'A', 25, 1, 'IN_PROGRESS', '2024-12-03 11:19:13', '2024-12-03 16:04:34'),
(4, 'CS301', '202401', 'FAC001', 'A', 20, 3, 'IN_PROGRESS', '2024-12-03 11:19:13', '2024-12-04 20:22:20'),
(5, 'MATH101', '202401', 'FAC003', 'A', 35, 2, 'IN_PROGRESS', '2024-12-03 11:19:13', '2024-12-04 20:22:20'),
(6, 'BUS101', '202401', 'FAC002', 'A', 40, 3, 'IN_PROGRESS', '2024-12-03 11:19:13', '2024-12-04 20:22:20'),
(7, 'CS101', '202402', 'FAC001', 'A', 30, 0, 'SCHEDULED', '2024-12-03 11:19:13', '2024-12-03 17:21:35'),
(8, 'CS201', '202402', 'FAC001', 'A', 25, 1, 'SCHEDULED', '2024-12-03 11:19:13', '2024-12-03 21:48:54'),
(9, 'MATH101', '202402', 'FAC003', 'A', 35, 0, 'SCHEDULED', '2024-12-03 11:19:13', '2024-12-03 13:36:58'),
(10, 'CS101', '202403', 'FAC001', 'A', 30, 0, 'SCHEDULED', '2024-12-03 11:19:13', '2024-12-03 13:36:58'),
(11, 'CS201', '202403', 'FAC001', 'A', 25, 0, 'SCHEDULED', '2024-12-03 11:19:13', '2024-12-03 13:36:58'),
(12, 'CS301', '202403', 'FAC001', 'A', 20, 0, 'SCHEDULED', '2024-12-03 11:19:13', '2024-12-03 13:36:58'),
(13, 'MATH101', '202403', 'FAC003', 'A', 35, 0, 'SCHEDULED', '2024-12-03 11:19:13', '2024-12-03 13:36:58'),
(14, 'BUS101', '202403', 'FAC002', 'A', 40, 0, 'SCHEDULED', '2024-12-03 11:19:13', '2024-12-03 13:36:58'),
(15, 'CS102', '202401', 'FAC001', 'A', 30, 0, 'SCHEDULED', '2024-12-03 13:36:58', '2024-12-03 13:36:58'),
(16, 'CS202', '202401', 'FAC001', 'A', 25, 3, 'SCHEDULED', '2024-12-03 13:36:58', '2024-12-04 20:22:20'),
(17, 'MATH201', '202401', 'FAC003', 'A', 35, 2, 'SCHEDULED', '2024-12-03 13:36:58', '2024-12-04 21:04:55'),
(18, 'BUS201', '202401', 'FAC002', 'A', 40, 1, 'SCHEDULED', '2024-12-03 13:36:58', '2024-12-04 20:22:20'),
(19, 'CS102', '202402', 'FAC001', 'A', 25, 1, 'SCHEDULED', '2024-12-03 13:36:58', '2024-12-03 17:21:44'),
(20, 'BUS201', '202402', 'FAC002', 'A', 35, 0, 'SCHEDULED', '2024-12-03 13:36:58', '2024-12-03 13:36:58'),
(21, 'ENG201', '202402', 'FAC003', 'A', 30, 1, 'SCHEDULED', '2024-12-03 13:36:58', '2024-12-03 21:48:38'),
(22, 'CS303', '202403', 'FAC001', 'A', 25, 0, 'SCHEDULED', '2024-12-03 13:36:58', '2024-12-03 13:36:58'),
(23, 'MATH201', '202403', 'FAC003', 'B', 35, 0, 'SCHEDULED', '2024-12-03 13:36:58', '2024-12-03 13:36:58'),
(24, 'BUS201', '202403', 'FAC002', 'B', 40, 0, 'SCHEDULED', '2024-12-03 13:36:58', '2024-12-03 13:36:58'),
(26, 'ENG201', '202403', 'FAC20241203110247', 'A', 30, 1, 'SCHEDULED', '2024-12-03 18:50:15', '2024-12-03 23:49:24'),
(27, 'CS301', '202403', 'FAC20241203110247', 'B', 25, 1, 'SCHEDULED', '2024-12-03 18:50:56', '2024-12-03 23:49:15'),
(40, 'CS101', '202310', 'FAC001', 'A', 30, 4, 'COMPLETED', '2024-12-04 19:47:39', '2024-12-04 20:22:20'),
(41, 'CS201', '202310', 'FAC001', 'A', 25, 3, 'COMPLETED', '2024-12-04 19:47:39', '2024-12-04 20:22:20'),
(42, 'CS301', '202310', 'FAC004', 'A', 20, 0, 'COMPLETED', '2024-12-04 19:47:39', '2024-12-04 20:22:20'),
(43, 'BUS101', '202310', 'FAC002', 'A', 35, 2, 'COMPLETED', '2024-12-04 19:47:39', '2024-12-04 20:22:20'),
(44, 'MATH101', '202310', 'FAC003', 'A', 30, 6, 'COMPLETED', '2024-12-04 19:47:39', '2024-12-04 20:22:20'),
(45, 'CS102', '202320', 'FAC008', 'A', 30, 1, 'COMPLETED', '2024-12-04 19:47:39', '2024-12-04 20:22:20'),
(46, 'CS202', '202320', 'FAC004', 'A', 25, 1, 'COMPLETED', '2024-12-04 19:47:39', '2024-12-04 20:22:20'),
(47, 'BUS201', '202320', 'FAC005', 'A', 35, 1, 'COMPLETED', '2024-12-04 19:47:39', '2024-12-04 20:22:20'),
(48, 'CS201', '202320', 'FAC001', 'B', 30, 0, 'COMPLETED', '2024-12-04 20:22:19', '2024-12-04 20:22:20'),
(49, 'CS301', '202320', 'FAC001', 'B', 25, 0, 'COMPLETED', '2024-12-04 20:22:19', '2024-12-04 20:22:20'),
(50, 'MATH101', '202320', 'FAC003', 'B', 35, 0, 'COMPLETED', '2024-12-04 20:22:19', '2024-12-04 20:22:20'),
(51, 'BUS101', '202320', 'FAC002', 'B', 40, 0, 'COMPLETED', '2024-12-04 20:22:19', '2024-12-04 20:22:20'),
(52, 'CS102', '202310', 'FAC001', 'B', 30, 0, 'COMPLETED', '2024-12-04 20:22:19', '2024-12-04 20:22:20'),
(53, 'CS202', '202310', 'FAC001', 'B', 25, 0, 'COMPLETED', '2024-12-04 20:22:19', '2024-12-04 20:22:20'),
(54, 'MATH201', '202310', 'FAC003', 'B', 35, 0, 'COMPLETED', '2024-12-04 20:22:19', '2024-12-04 20:22:20'),
(55, 'BUS201', '202310', 'FAC002', 'B', 40, 1, 'COMPLETED', '2024-12-04 20:22:19', '2024-12-04 20:22:20'),
(56, 'CS303', '202320', 'FAC20241203110247', 'B', 28, 0, 'SCHEDULED', '2024-12-04 21:11:12', '2024-12-04 21:11:12');

-- --------------------------------------------------------

--
-- Stand-in structure for view `course_roster_details`
-- (See below for the actual view)
--
CREATE TABLE `course_roster_details` (
`enrollmentID` int(11)
,`courseOfferingID` int(11)
,`studentID` varchar(50)
,`firstName` varchar(100)
,`lastName` varchar(100)
,`email` varchar(100)
,`programCode` varchar(10)
,`enrollmentStatus` varchar(50)
,`enrollmentDate` datetime
,`termCode` varchar(20)
,`facultyID` varchar(50)
);

-- --------------------------------------------------------

--
-- Table structure for table `course_schedule`
--

CREATE TABLE `course_schedule` (
  `id` int(11) NOT NULL,
  `course_offering_id` int(11) NOT NULL,
  `day_of_week` enum('MONDAY','TUESDAY','WEDNESDAY','THURSDAY','FRIDAY','SATURDAY','SUNDAY') NOT NULL,
  `start_time` time NOT NULL,
  `end_time` time NOT NULL,
  `room_number` varchar(20) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `course_schedule`
--

INSERT INTO `course_schedule` (`id`, `course_offering_id`, `day_of_week`, `start_time`, `end_time`, `room_number`) VALUES
(4, 19, 'MONDAY', '09:00:00', '10:30:00', 'CS-101'),
(5, 16, 'WEDNESDAY', '11:00:00', '12:30:00', 'CS-102'),
(6, 3, 'FRIDAY', '14:00:00', '15:30:00', 'CS-103'),
(7, 1, 'MONDAY', '08:00:00', '09:30:00', 'CS-201'),
(8, 1, 'WEDNESDAY', '08:00:00', '09:30:00', 'CS-201'),
(9, 2, 'MONDAY', '09:45:00', '11:15:00', 'CS-202'),
(10, 2, 'WEDNESDAY', '09:45:00', '11:15:00', 'CS-202'),
(11, 4, 'MONDAY', '11:30:00', '13:00:00', 'CS-203'),
(12, 4, 'WEDNESDAY', '11:30:00', '13:00:00', 'CS-203'),
(13, 5, 'TUESDAY', '08:00:00', '09:30:00', 'MATH-101'),
(14, 5, 'THURSDAY', '08:00:00', '09:30:00', 'MATH-101'),
(15, 6, 'TUESDAY', '09:45:00', '11:15:00', 'BUS-101'),
(16, 6, 'THURSDAY', '09:45:00', '11:15:00', 'BUS-101'),
(17, 15, 'TUESDAY', '11:30:00', '13:00:00', 'CS-204'),
(18, 15, 'THURSDAY', '11:30:00', '13:00:00', 'CS-204'),
(19, 17, 'MONDAY', '14:00:00', '15:30:00', 'MATH-102'),
(20, 17, 'WEDNESDAY', '14:00:00', '15:30:00', 'MATH-102'),
(21, 18, 'MONDAY', '15:45:00', '17:15:00', 'BUS-102'),
(22, 18, 'WEDNESDAY', '15:45:00', '17:15:00', 'BUS-102'),
(23, 20, 'TUESDAY', '14:00:00', '15:30:00', 'BUS-103'),
(24, 20, 'THURSDAY', '14:00:00', '15:30:00', 'BUS-103'),
(25, 21, 'TUESDAY', '15:45:00', '17:15:00', 'ENG-101'),
(26, 21, 'THURSDAY', '15:45:00', '17:15:00', 'ENG-101'),
(27, 22, 'FRIDAY', '09:00:00', '12:00:00', 'CS-301'),
(28, 23, 'FRIDAY', '13:00:00', '16:00:00', 'MATH-201'),
(29, 24, 'FRIDAY', '09:00:00', '12:00:00', 'BUS-201'),
(30, 8, 'MONDAY', '13:00:00', '14:30:00', 'CS-204'),
(31, 8, 'WEDNESDAY', '13:00:00', '14:30:00', 'CS-204'),
(32, 40, 'MONDAY', '09:00:00', '10:30:00', 'ROOM-174'),
(33, 41, 'MONDAY', '09:00:00', '10:30:00', 'ROOM-179'),
(34, 42, 'MONDAY', '09:00:00', '10:30:00', 'ROOM-177'),
(35, 43, 'MONDAY', '09:00:00', '10:30:00', 'ROOM-147'),
(36, 44, 'MONDAY', '09:00:00', '10:30:00', 'ROOM-104'),
(37, 45, 'MONDAY', '09:00:00', '10:30:00', 'ROOM-181'),
(38, 46, 'MONDAY', '09:00:00', '10:30:00', 'ROOM-194'),
(39, 47, 'MONDAY', '09:00:00', '10:30:00', 'ROOM-128'),
(47, 40, 'WEDNESDAY', '09:00:00', '10:30:00', 'ROOM-159'),
(48, 41, 'WEDNESDAY', '09:00:00', '10:30:00', 'ROOM-110'),
(49, 42, 'WEDNESDAY', '09:00:00', '10:30:00', 'ROOM-173'),
(50, 43, 'WEDNESDAY', '09:00:00', '10:30:00', 'ROOM-135'),
(51, 44, 'WEDNESDAY', '09:00:00', '10:30:00', 'ROOM-157'),
(52, 45, 'WEDNESDAY', '09:00:00', '10:30:00', 'ROOM-181'),
(53, 46, 'WEDNESDAY', '09:00:00', '10:30:00', 'ROOM-136'),
(54, 47, 'WEDNESDAY', '09:00:00', '10:30:00', 'ROOM-137'),
(62, 51, 'WEDNESDAY', '09:00:00', '10:30:00', 'ROOM-190'),
(63, 14, 'MONDAY', '09:00:00', '10:30:00', 'ROOM-180'),
(64, 55, 'WEDNESDAY', '09:00:00', '10:30:00', 'ROOM-133'),
(65, 7, 'MONDAY', '09:00:00', '10:30:00', 'ROOM-123'),
(66, 10, 'MONDAY', '09:00:00', '10:30:00', 'ROOM-119'),
(67, 52, 'WEDNESDAY', '09:00:00', '10:30:00', 'ROOM-127'),
(68, 48, 'WEDNESDAY', '09:00:00', '10:30:00', 'ROOM-179'),
(69, 11, 'MONDAY', '09:00:00', '10:30:00', 'ROOM-111'),
(70, 53, 'WEDNESDAY', '09:00:00', '10:30:00', 'ROOM-122'),
(71, 49, 'WEDNESDAY', '09:00:00', '10:30:00', 'ROOM-174'),
(72, 12, 'MONDAY', '09:00:00', '10:30:00', 'ROOM-107'),
(73, 27, 'WEDNESDAY', '09:00:00', '10:30:00', 'ROOM-113'),
(74, 26, 'MONDAY', '09:00:00', '10:30:00', 'ROOM-143'),
(75, 50, 'WEDNESDAY', '09:00:00', '10:30:00', 'ROOM-177'),
(76, 9, 'MONDAY', '09:00:00', '10:30:00', 'ROOM-157'),
(77, 13, 'MONDAY', '09:00:00', '10:30:00', 'ROOM-154'),
(78, 54, 'WEDNESDAY', '09:00:00', '10:30:00', 'ROOM-199');

-- --------------------------------------------------------

--
-- Table structure for table `department`
--

CREATE TABLE `department` (
  `id` int(11) NOT NULL,
  `departmentCode` varchar(10) NOT NULL,
  `departmentName` varchar(100) NOT NULL,
  `headOfDepartmentID` varchar(50) DEFAULT NULL,
  `dateCreated` datetime DEFAULT current_timestamp(),
  `lastModified` datetime DEFAULT current_timestamp() ON UPDATE current_timestamp(),
  `isActive` tinyint(1) DEFAULT 1
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `department`
--

INSERT INTO `department` (`id`, `departmentCode`, `departmentName`, `headOfDepartmentID`, `dateCreated`, `lastModified`, `isActive`) VALUES
(1, 'CSE', 'Computer Science and Information Systems', NULL, '2024-12-02 21:05:19', '2024-12-02 21:05:19', 1),
(2, 'BUS', 'Business', NULL, '2024-12-02 21:05:19', '2024-12-02 21:05:19', 1),
(3, 'HUM', 'Humanities and Social Sciences', NULL, '2024-12-02 21:05:19', '2024-12-02 21:05:19', 1),
(4, 'ENG', 'Engineering', NULL, '2024-12-02 21:05:19', '2024-12-02 21:05:19', 1);

-- --------------------------------------------------------

--
-- Table structure for table `enrollment`
--

CREATE TABLE `enrollment` (
  `id` int(11) NOT NULL,
  `studentID` varchar(50) NOT NULL,
  `courseOfferingID` int(11) NOT NULL,
  `enrollmentDate` datetime DEFAULT current_timestamp(),
  `statusID` int(11) NOT NULL,
  `lastModified` datetime DEFAULT current_timestamp() ON UPDATE current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `enrollment`
--

INSERT INTO `enrollment` (`id`, `studentID`, `courseOfferingID`, `enrollmentDate`, `statusID`, `lastModified`) VALUES
(1, 'STU20241202234039', 1, '2024-12-03 11:54:41', 2, '2024-12-03 12:49:06'),
(21, 'STU20241202234039', 5, '2024-12-03 12:11:58', 2, '2024-12-03 12:43:41'),
(22, 'STU001', 3, '2024-12-03 12:11:58', 1, '2024-12-03 12:11:58'),
(23, 'STU001', 4, '2024-12-03 12:11:58', 1, '2024-12-03 12:11:58'),
(24, 'STU002', 6, '2024-12-03 12:11:58', 1, '2024-12-03 12:11:58'),
(25, 'STU002', 5, '2024-12-03 12:11:58', 1, '2024-12-03 12:11:58'),
(26, 'STU005', 1, '2024-12-03 12:11:58', 1, '2024-12-03 12:11:58'),
(27, 'STU005', 6, '2024-12-03 12:11:58', 1, '2024-12-03 12:11:58'),
(28, 'STU20241202234039', 3, '2024-12-03 12:43:01', 2, '2024-12-03 16:04:34'),
(29, 'STU20241202234039', 2, '2024-12-03 12:45:06', 2, '2024-12-03 12:46:25'),
(30, 'STU20241202234039', 6, '2024-12-03 12:45:48', 2, '2024-12-03 16:05:30'),
(31, 'STU20241202234039', 4, '2024-12-03 13:01:26', 2, '2024-12-03 16:05:06'),
(32, 'STU20241202234039', 18, '2024-12-03 16:05:43', 2, '2024-12-03 17:37:29'),
(33, 'STU20241202234039', 17, '2024-12-03 17:20:52', 2, '2024-12-04 21:04:55'),
(34, 'STU20241202234039', 7, '2024-12-03 17:21:31', 2, '2024-12-03 17:21:35'),
(35, 'STU20241202234039', 19, '2024-12-03 17:21:44', 1, '2024-12-03 17:21:44'),
(36, 'STU20241202234039', 16, '2024-12-03 17:23:10', 1, '2024-12-03 17:23:10'),
(56, 'STU20241202234039', 21, '2024-12-03 21:48:38', 1, '2024-12-03 21:48:38'),
(57, 'STU20241202234039', 8, '2024-12-03 21:48:54', 1, '2024-12-03 21:48:54'),
(58, 'STU20241202234039', 27, '2024-12-03 23:49:15', 1, '2024-12-03 23:49:15'),
(59, 'STU20241202234039', 26, '2024-12-03 23:49:24', 1, '2024-12-03 23:49:24'),
(60, 'STU010', 40, '2024-12-04 19:47:39', 3, '2024-12-04 19:47:39'),
(61, 'STU010', 41, '2024-12-04 19:47:39', 3, '2024-12-04 19:47:39'),
(62, 'STU010', 44, '2024-12-04 19:47:39', 3, '2024-12-04 19:47:39'),
(63, 'STU011', 43, '2024-12-04 19:47:39', 3, '2024-12-04 19:47:39'),
(64, 'STU011', 44, '2024-12-04 19:47:39', 3, '2024-12-04 19:47:39'),
(66, 'STU012', 40, '2024-12-04 19:47:39', 3, '2024-12-04 19:47:39'),
(67, 'STU012', 44, '2024-12-04 19:47:39', 3, '2024-12-04 19:47:39'),
(69, 'STU013', 45, '2024-12-04 19:47:39', 3, '2024-12-04 19:47:39'),
(70, 'STU013', 46, '2024-12-04 19:47:39', 3, '2024-12-04 19:47:39'),
(72, 'STU014', 47, '2024-12-04 19:47:39', 3, '2024-12-04 19:47:39'),
(73, 'STU015', 40, '2023-09-01 00:00:00', 3, '2024-12-04 20:22:20'),
(74, 'STU015', 41, '2023-09-01 00:00:00', 3, '2024-12-04 20:22:20'),
(75, 'STU015', 44, '2023-09-01 00:00:00', 3, '2024-12-04 20:22:20'),
(76, 'STU016', 43, '2023-09-01 00:00:00', 3, '2024-12-04 20:22:20'),
(77, 'STU016', 55, '2023-09-01 00:00:00', 3, '2024-12-04 20:22:20'),
(78, 'STU016', 44, '2023-09-01 00:00:00', 3, '2024-12-04 20:22:20'),
(79, 'STU017', 40, '2023-09-01 00:00:00', 3, '2024-12-04 20:22:20'),
(80, 'STU017', 41, '2023-09-01 00:00:00', 3, '2024-12-04 20:22:20'),
(81, 'STU017', 44, '2023-09-01 00:00:00', 3, '2024-12-04 20:22:20'),
(82, 'STU018', 16, '2024-12-04 00:00:00', 1, '2024-12-04 20:22:20'),
(83, 'STU018', 4, '2024-12-04 00:00:00', 1, '2024-12-04 20:22:20'),
(84, 'STU018', 17, '2024-12-04 00:00:00', 1, '2024-12-04 20:22:20'),
(85, 'STU019', 6, '2024-12-04 00:00:00', 1, '2024-12-04 20:22:20'),
(86, 'STU019', 18, '2024-12-04 00:00:00', 1, '2024-12-04 20:22:20'),
(87, 'STU019', 5, '2024-12-04 00:00:00', 1, '2024-12-04 20:22:20'),
(88, 'STU020', 16, '2024-12-04 00:00:00', 1, '2024-12-04 20:22:20'),
(89, 'STU020', 4, '2024-12-04 00:00:00', 1, '2024-12-04 20:22:20'),
(90, 'STU020', 17, '2024-12-04 00:00:00', 1, '2024-12-04 20:22:20');

-- --------------------------------------------------------

--
-- Table structure for table `enrollment_status`
--

CREATE TABLE `enrollment_status` (
  `id` int(11) NOT NULL,
  `statusName` varchar(50) NOT NULL,
  `description` text DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `enrollment_status`
--

INSERT INTO `enrollment_status` (`id`, `statusName`, `description`) VALUES
(1, 'ENROLLED', 'Currently enrolled in the course'),
(2, 'WITHDRAWN', 'Withdrawn from the course'),
(3, 'COMPLETED', 'Successfully completed the course'),
(4, 'INCOMPLETE', 'Course not completed');

-- --------------------------------------------------------

--
-- Table structure for table `faculty`
--

CREATE TABLE `faculty` (
  `id` int(11) NOT NULL,
  `userID` varchar(50) NOT NULL,
  `departmentCode` varchar(10) NOT NULL,
  `title` varchar(50) DEFAULT NULL,
  `specialization` varchar(100) DEFAULT NULL,
  `dateOfAppointment` date NOT NULL,
  `employmentStatus` enum('FULL_TIME','PART_TIME','ADJUNCT') DEFAULT 'FULL_TIME',
  `dateCreated` datetime DEFAULT current_timestamp(),
  `lastModified` datetime DEFAULT current_timestamp() ON UPDATE current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `faculty`
--

INSERT INTO `faculty` (`id`, `userID`, `departmentCode`, `title`, `specialization`, `dateOfAppointment`, `employmentStatus`, `dateCreated`, `lastModified`) VALUES
(1, 'FAC20241203110247', 'CSE', 'Associate Professor', 'Data structures and algorithms as well as object-oriented programming and web development', '2024-12-04', 'FULL_TIME', '2024-12-03 11:02:47', '2024-12-04 21:10:31'),
(2, 'FAC001', 'CSE', 'Professor', 'Computer Science', '2020-01-01', 'FULL_TIME', '2024-12-03 11:19:13', '2024-12-03 11:19:13'),
(3, 'FAC002', 'BUS', 'Associate Professor', 'Business Administration', '2020-01-01', 'FULL_TIME', '2024-12-03 11:19:13', '2024-12-03 11:19:13'),
(4, 'FAC003', 'ENG', 'Assistant Professor', 'Engineering', '2020-01-01', 'FULL_TIME', '2024-12-03 11:19:13', '2024-12-03 11:19:13'),
(6, 'FAC20241203002', 'BUS', 'Associate Professor', 'Financial Economics and Business Analytics', '2024-02-01', 'FULL_TIME', '2024-12-03 13:17:29', '2024-12-03 13:17:29'),
(7, 'FAC20241203003', 'ENG', 'Assistant Professor', 'Robotics and Control Systems', '2024-01-20', 'FULL_TIME', '2024-12-03 13:17:29', '2024-12-03 13:17:29'),
(8, 'FAC20241203004', 'HUM', 'Senior Lecturer', 'Modern Literature and Creative Writing', '2024-02-15', 'PART_TIME', '2024-12-03 13:17:29', '2024-12-03 13:17:29'),
(9, 'FAC004', 'CSE', 'Associate Professor', 'Machine Learning', '2020-01-01', 'FULL_TIME', '2024-12-04 19:43:54', '2024-12-04 19:43:54'),
(10, 'FAC005', 'BUS', 'Professor', 'Marketing', '2019-01-01', 'FULL_TIME', '2024-12-04 19:43:54', '2024-12-04 19:43:54'),
(11, 'FAC006', 'ENG', 'Assistant Professor', 'Robotics', '2021-01-01', 'FULL_TIME', '2024-12-04 19:43:54', '2024-12-04 19:43:54'),
(12, 'FAC007', 'HUM', 'Associate Professor', 'Psychology', '2020-06-01', 'FULL_TIME', '2024-12-04 19:43:54', '2024-12-04 19:43:54'),
(13, 'FAC008', 'CSE', 'Professor', 'Cybersecurity', '2018-01-01', 'FULL_TIME', '2024-12-04 19:43:54', '2024-12-04 19:43:54');

-- --------------------------------------------------------

--
-- Stand-in structure for view `faculty_course_offerings`
-- (See below for the actual view)
--
CREATE TABLE `faculty_course_offerings` (
`courseOfferingID` int(11)
,`termCode` varchar(20)
,`courseCode` varchar(20)
,`section` varchar(10)
,`courseName` varchar(100)
,`courseDisplay` varchar(144)
,`facultyID` varchar(50)
,`enrolledCount` int(11)
,`capacity` int(11)
,`status` enum('SCHEDULED','IN_PROGRESS','COMPLETED','CANCELLED')
);

-- --------------------------------------------------------

--
-- Table structure for table `grade`
--

CREATE TABLE `grade` (
  `id` int(11) NOT NULL,
  `enrollmentID` int(11) NOT NULL,
  `grade` varchar(2) NOT NULL,
  `submissionDate` datetime DEFAULT current_timestamp(),
  `lastModified` datetime DEFAULT current_timestamp() ON UPDATE current_timestamp(),
  `submittedBy` varchar(50) NOT NULL,
  `comments` text DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `grade`
--

INSERT INTO `grade` (`id`, `enrollmentID`, `grade`, `submissionDate`, `lastModified`, `submittedBy`, `comments`) VALUES
(1, 32, 'A', '2024-12-03 17:30:33', '2024-12-03 17:30:33', 'FAC002', 'Excellent work'),
(2, 36, 'B+', '2024-12-03 17:30:33', '2024-12-03 17:30:33', 'FAC001', 'Good understanding of concepts'),
(7, 49, 'A', '2024-12-03 18:12:28', '2024-12-03 18:12:28', 'FAC001', 'Excellent work throughout the semester'),
(8, 50, 'B+', '2024-12-03 18:12:28', '2024-12-03 18:12:28', 'FAC001', 'Good understanding of concepts'),
(9, 51, 'A-', '2024-12-03 18:12:28', '2024-12-03 18:12:28', 'FAC001', 'Very good performance'),
(10, 52, 'B', '2024-12-03 18:12:28', '2024-12-03 18:12:28', 'FAC003', 'Above average work'),
(14, 58, 'A', '2024-12-04 12:19:01', '2024-12-04 21:11:57', 'FAC20241203110247', 'Good work'),
(15, 60, 'A', '2024-12-04 19:47:39', '2024-12-04 19:47:39', 'FAC001', 'Course completed successfully'),
(16, 61, 'A', '2024-12-04 19:47:39', '2024-12-04 19:47:39', 'FAC001', 'Course completed successfully'),
(17, 62, 'A', '2024-12-04 19:47:39', '2024-12-04 19:47:39', 'FAC003', 'Course completed successfully'),
(18, 63, 'B+', '2024-12-04 19:47:39', '2024-12-04 19:47:39', 'FAC002', 'Course completed successfully'),
(19, 64, 'B+', '2024-12-04 19:47:39', '2024-12-04 19:47:39', 'FAC003', 'Course completed successfully'),
(20, 66, 'A-', '2024-12-04 19:47:39', '2024-12-04 19:47:39', 'FAC001', 'Course completed successfully'),
(21, 67, 'A-', '2024-12-04 19:47:39', '2024-12-04 19:47:39', 'FAC003', 'Course completed successfully'),
(22, 69, 'B', '2024-12-04 19:47:39', '2024-12-04 19:47:39', 'FAC008', 'Course completed successfully'),
(23, 70, 'B', '2024-12-04 19:47:39', '2024-12-04 19:47:39', 'FAC004', 'Course completed successfully'),
(24, 72, 'B+', '2024-12-04 19:47:39', '2024-12-04 19:47:39', 'FAC005', 'Course completed successfully'),
(30, 73, 'A', '2024-12-04 20:22:20', '2024-12-04 20:22:20', 'FAC001', 'Course completed with good performance'),
(31, 74, 'A', '2024-12-04 20:22:20', '2024-12-04 20:22:20', 'FAC001', 'Course completed with good performance'),
(32, 75, 'A', '2024-12-04 20:22:20', '2024-12-04 20:22:20', 'FAC003', 'Course completed with good performance'),
(33, 76, 'B+', '2024-12-04 20:22:20', '2024-12-04 20:22:20', 'FAC002', 'Course completed with good performance'),
(34, 77, 'B+', '2024-12-04 20:22:20', '2024-12-04 20:22:20', 'FAC002', 'Course completed with good performance'),
(35, 78, 'B+', '2024-12-04 20:22:20', '2024-12-04 20:22:20', 'FAC003', 'Course completed with good performance'),
(36, 79, 'A-', '2024-12-04 20:22:20', '2024-12-04 20:22:20', 'FAC001', 'Course completed with good performance'),
(37, 80, 'A-', '2024-12-04 20:22:20', '2024-12-04 20:22:20', 'FAC001', 'Course completed with good performance'),
(38, 81, 'A-', '2024-12-04 20:22:20', '2024-12-04 20:22:20', 'FAC003', 'Course completed with good performance'),
(45, 59, 'A', '2024-12-04 21:12:21', '2024-12-04 21:12:21', 'FAC20241203110247', 'Nice Try');

-- --------------------------------------------------------

--
-- Table structure for table `grade_scale`
--

CREATE TABLE `grade_scale` (
  `id` int(11) NOT NULL,
  `grade` varchar(2) NOT NULL,
  `minPercentage` decimal(5,2) NOT NULL,
  `maxPercentage` decimal(5,2) NOT NULL,
  `gradePoint` decimal(3,2) NOT NULL,
  `description` varchar(100) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `grade_scale`
--

INSERT INTO `grade_scale` (`id`, `grade`, `minPercentage`, `maxPercentage`, `gradePoint`, `description`) VALUES
(1, 'A+', 97.00, 100.00, 4.00, 'Exceptional'),
(2, 'A', 93.00, 96.99, 4.00, 'Excellent'),
(3, 'A-', 90.00, 92.99, 3.70, 'Very Good'),
(4, 'B+', 87.00, 89.99, 3.30, 'Good'),
(5, 'B', 83.00, 86.99, 3.00, 'Above Average'),
(6, 'B-', 80.00, 82.99, 2.70, 'Average'),
(7, 'C+', 77.00, 79.99, 2.30, 'Below Average'),
(8, 'C', 73.00, 76.99, 2.00, 'Fair'),
(9, 'C-', 70.00, 72.99, 1.70, 'Poor'),
(10, 'D+', 67.00, 69.99, 1.30, 'Very Poor'),
(11, 'D', 63.00, 66.99, 1.00, 'Passing'),
(12, 'F', 0.00, 62.99, 0.00, 'Failing');

-- --------------------------------------------------------

--
-- Table structure for table `student`
--

CREATE TABLE `student` (
  `id` int(11) NOT NULL,
  `userID` varchar(50) NOT NULL,
  `studentID` varchar(50) NOT NULL,
  `programCode` varchar(10) NOT NULL,
  `batch` varchar(10) NOT NULL,
  `admissionDate` date DEFAULT NULL,
  `expectedGraduationDate` date DEFAULT NULL,
  `dateCreated` datetime DEFAULT current_timestamp(),
  `lastModified` datetime DEFAULT current_timestamp() ON UPDATE current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `student`
--

INSERT INTO `student` (`id`, `userID`, `studentID`, `programCode`, `batch`, `admissionDate`, `expectedGraduationDate`, `dateCreated`, `lastModified`) VALUES
(1, 'STU20241202234039', 'STU20241202234039', 'CS-BSC', '2026', '2024-12-04', '2024-12-04', '2024-12-02 23:40:39', '2024-12-04 20:54:18'),
(7, 'STU001', 'STU001', 'CS', '2024', '2024-01-15', '2028-05-15', '2024-12-03 12:06:54', '2024-12-03 12:06:54'),
(8, 'STU002', 'STU002', 'MIS', '2024', '2024-01-15', '2028-05-15', '2024-12-03 12:06:54', '2024-12-03 12:06:54'),
(9, 'STU005', 'STU005', 'ME', '2024', '2024-01-15', '2028-05-15', '2024-12-03 12:06:54', '2024-12-03 12:06:54'),
(13, 'STU010', 'STU010', 'CS-BSC', '2024', '2024-01-15', '2028-05-15', '2024-12-04 19:47:39', '2024-12-04 19:47:39'),
(14, 'STU011', 'STU011', 'BBA', '2024', '2024-01-15', '2028-05-15', '2024-12-04 19:47:39', '2024-12-04 19:47:39'),
(15, 'STU012', 'STU012', 'ME-BSC', '2024', '2024-01-15', '2028-05-15', '2024-12-04 19:47:39', '2024-12-04 19:47:39'),
(16, 'STU013', 'STU013', 'CS-BSC', '2024', '2024-01-15', '2028-05-15', '2024-12-04 19:47:39', '2024-12-04 19:47:39'),
(17, 'STU014', 'STU014', 'BBA', '2024', '2024-01-15', '2028-05-15', '2024-12-04 19:47:39', '2024-12-04 19:47:39'),
(18, 'STU015', 'STU015', 'CS-BSC', '2024', '2024-01-15', '2028-05-15', '2024-12-04 20:22:19', '2024-12-04 20:22:19'),
(19, 'STU016', 'STU016', 'BBA', '2024', '2024-01-15', '2028-05-15', '2024-12-04 20:22:19', '2024-12-04 20:22:19'),
(20, 'STU017', 'STU017', 'ME-BSC', '2024', '2024-01-15', '2028-05-15', '2024-12-04 20:22:19', '2024-12-04 20:22:19'),
(21, 'STU018', 'STU018', 'CS-MSC', '2024', '2024-01-15', '2026-05-15', '2024-12-04 20:22:19', '2024-12-04 20:22:19'),
(22, 'STU019', 'STU019', 'MBA', '2024', '2024-01-15', '2026-05-15', '2024-12-04 20:22:19', '2024-12-04 20:22:19'),
(23, 'STU020', 'STU020', 'AI', '2024', '2024-01-15', '2026-05-15', '2024-12-04 20:22:19', '2024-12-04 20:22:19'),
(24, 'STU20241204210134', 'STU20241204210134', 'MIS', '2026', '2024-12-04', '2024-12-04', '2024-12-04 21:01:34', '2024-12-04 21:02:53');

-- --------------------------------------------------------

--
-- Stand-in structure for view `student_grades`
-- (See below for the actual view)
--
CREATE TABLE `student_grades` (
`studentID` varchar(50)
,`termCode` varchar(20)
,`courseCode` varchar(20)
,`courseName` varchar(100)
,`credits` int(11)
,`grade` varchar(2)
,`gradePoint` decimal(3,2)
,`submissionDate` datetime
);

-- --------------------------------------------------------

--
-- Table structure for table `user`
--

CREATE TABLE `user` (
  `id` int(11) NOT NULL,
  `userID` varchar(50) NOT NULL,
  `firstName` varchar(100) NOT NULL,
  `lastName` varchar(100) NOT NULL,
  `email` varchar(100) NOT NULL,
  `password` varchar(255) NOT NULL,
  `roleID` int(11) NOT NULL,
  `username` varchar(50) DEFAULT NULL,
  `dateCreated` datetime DEFAULT current_timestamp(),
  `lastModified` datetime DEFAULT current_timestamp() ON UPDATE current_timestamp(),
  `isActive` tinyint(1) DEFAULT 1
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `user`
--

INSERT INTO `user` (`id`, `userID`, `firstName`, `lastName`, `email`, `password`, `roleID`, `username`, `dateCreated`, `lastModified`, `isActive`) VALUES
(2, 'STU20241202234039', 'Aseda', 'The Great', 'biohaseda07@gmail.com', 'FatherAbraham2', 3, 'donchuku', '2024-12-02 23:40:39', '2024-12-04 20:54:18', 1),
(3, 'FAC20241203110247', 'Kwaku', 'Yeluripati', 'govs.yeluripati@gmail.com', 'FatherAbraham2', 2, 'Dr. Govs', '2024-12-03 11:02:47', '2024-12-04 21:10:31', 1),
(4, 'FAC001', 'John', 'Smith', 'john.smith@university.edu', 'password123', 2, 'jsmith', '2024-12-03 11:19:13', '2024-12-03 11:19:13', 1),
(5, 'FAC002', 'Mary', 'Johnson', 'mary.johnson@university.edu', 'password123', 2, 'mjohnson', '2024-12-03 11:19:13', '2024-12-03 11:19:13', 1),
(6, 'FAC003', 'Robert', 'Wilson', 'robert.wilson@university.edu', 'password123', 2, 'rwilson', '2024-12-03 11:19:13', '2024-12-03 11:19:13', 1),
(7, 'STU001', 'James', 'Brown', 'james.brown@student.edu', 'password123', 3, 'jbrown', '2024-12-03 11:19:13', '2024-12-03 11:19:13', 1),
(8, 'STU002', 'Sarah', 'Davis', 'sarah.davis@student.edu', 'password123', 3, 'sdavis', '2024-12-03 11:19:13', '2024-12-04 12:45:39', 0),
(9, 'ADMIN20241204001', 'Admin', 'User', 'admin@example.com', 'secureHashedPassword123', 1, 'adminuser', '2024-12-04 00:10:22', '2024-12-04 00:10:22', 1),
(15, 'STU005', 'Michael', 'Lee', 'michael.lee@student.edu', 'password123', 3, 'mlee', '2024-12-03 12:01:36', '2024-12-03 12:01:36', 1),
(18, 'FAC20241203002', 'Jennifer', 'Martinez', 'jennifer.martinez@university.edu', 'hashedPassword123', 2, 'jmartinez', '2024-12-03 13:17:29', '2024-12-03 13:17:29', 1),
(19, 'FAC20241203003', 'Michael', 'Chen', 'michael.chen@university.edu', 'hashedPassword123', 2, 'mchen', '2024-12-03 13:17:29', '2024-12-03 13:17:29', 1),
(20, 'FAC20241203004', 'Sarah', 'Thompson', 'sarah.thompson@university.edu', 'hashedPassword123', 2, 'sthompson', '2024-12-03 13:17:29', '2024-12-03 13:17:29', 1),
(21, 'STU20241204124441', 'John', 'Cena', 'cena@gmail.com', 'FatherAbraham2', 3, 'CantSeeMe', '2024-12-04 12:44:41', '2024-12-04 12:44:41', 1),
(22, 'FAC004', 'David', 'Brown', 'david.brown@university.edu', 'password123', 2, 'dbrown', '2024-12-04 19:43:54', '2024-12-04 19:43:54', 1),
(23, 'FAC005', 'Emily', 'Taylor', 'emily.taylor@university.edu', 'password123', 2, 'etaylor', '2024-12-04 19:43:54', '2024-12-04 19:43:54', 1),
(24, 'FAC006', 'James', 'Wilson', 'james.wilson@university.edu', 'password123', 2, 'jwilson', '2024-12-04 19:43:54', '2024-12-04 19:43:54', 1),
(25, 'FAC007', 'Sophie', 'Anderson', 'sophie.anderson@university.edu', 'password123', 2, 'sanderson', '2024-12-04 19:43:54', '2024-12-04 19:43:54', 1),
(26, 'FAC008', 'William', 'Davis', 'william.davis@university.edu', 'password123', 2, 'wdavis', '2024-12-04 19:43:54', '2024-12-04 19:43:54', 1),
(32, 'STU010', 'Alice', 'Johnson', 'alice.johnson2024@student.edu', 'password123', 3, 'ajohnson2024', '2024-12-04 19:47:39', '2024-12-04 19:47:39', 1),
(33, 'STU011', 'Bob', 'Smith', 'bob.smith2024@student.edu', 'password123', 3, 'bsmith2024', '2024-12-04 19:47:39', '2024-12-04 19:47:39', 1),
(34, 'STU012', 'Carol', 'Wilson', 'carol.wilson2024@student.edu', 'password123', 3, 'cwilson2024', '2024-12-04 19:47:39', '2024-12-04 19:47:39', 1),
(35, 'STU013', 'Daniel', 'Brown', 'daniel.brown2024@student.edu', 'password123', 3, 'dbrown2024', '2024-12-04 19:47:39', '2024-12-04 19:47:39', 1),
(36, 'STU014', 'Emma', 'Davis', 'emma.davis2024@student.edu', 'password123', 3, 'edavis2024', '2024-12-04 19:47:39', '2024-12-04 19:47:39', 1),
(37, 'STU015', 'Frank', 'Miller', 'frank.miller@student.edu', 'password123', 3, 'fmiller', '2024-12-04 20:22:19', '2024-12-04 20:22:19', 1),
(38, 'STU016', 'Grace', 'White', 'grace.white@student.edu', 'password123', 3, 'gwhite', '2024-12-04 20:22:19', '2024-12-04 20:22:19', 1),
(39, 'STU017', 'Henry', 'Black', 'henry.black@student.edu', 'password123', 3, 'hblack', '2024-12-04 20:22:19', '2024-12-04 20:22:19', 1),
(40, 'STU018', 'Isabella', 'Green', 'isabella.green@student.edu', 'password123', 3, 'igreen', '2024-12-04 20:22:19', '2024-12-04 20:22:19', 1),
(41, 'STU019', 'Jack', 'Taylor', 'jack.taylor@student.edu', 'password123', 3, 'jtaylor', '2024-12-04 20:22:19', '2024-12-04 20:22:19', 1),
(42, 'STU020', 'Kelly', 'Adams', 'kelly.adams@student.edu', 'password123', 3, 'kadams', '2024-12-04 20:22:19', '2024-12-04 20:22:19', 1),
(43, 'STU20241204203130', 'Burna', 'Boy', 'burna@gmail.com', 'burnzy123', 3, 'BurnaBoy', '2024-12-04 20:31:30', '2024-12-04 20:31:30', 1),
(44, 'STU20241204210134', 'Jamal', 'Abdullah', 'bioh@gmail.com', 'FatherAbraham2', 3, 'bioh123', '2024-12-04 21:01:34', '2024-12-04 21:02:53', 1),
(45, 'FAC20241204211941', 'Susan', 'Merlin', 'susan.merlin@gmail.com', 'susAnMerlin2024', 2, 'sMerlin1', '2024-12-04 21:19:41', '2024-12-04 21:20:18', 0);

-- --------------------------------------------------------

--
-- Table structure for table `user_role`
--

CREATE TABLE `user_role` (
  `id` int(11) NOT NULL,
  `roleName` varchar(50) NOT NULL,
  `description` text DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- Dumping data for table `user_role`
--

INSERT INTO `user_role` (`id`, `roleName`, `description`) VALUES
(1, 'ADMIN', 'System Administrator'),
(2, 'FACULTY', 'Teaching Faculty'),
(3, 'STUDENT', 'Enrolled Student'),
(4, 'STAFF', 'Administrative Staff');

-- --------------------------------------------------------

--
-- Stand-in structure for view `vw_active_departments`
-- (See below for the actual view)
--
CREATE TABLE `vw_active_departments` (
`departmentCode` varchar(10)
,`departmentName` varchar(100)
,`headOfDepartmentID` varchar(50)
);

-- --------------------------------------------------------

--
-- Stand-in structure for view `vw_program_enrollment_stats`
-- (See below for the actual view)
--
CREATE TABLE `vw_program_enrollment_stats` (
`programCode` varchar(10)
,`programName` varchar(100)
,`departmentCode` varchar(10)
,`degreeLevel` enum('UNDERGRADUATE','GRADUATE','DOCTORAL')
,`totalStudents` bigint(21)
,`earliestAdmission` date
,`latestAdmission` date
);

-- --------------------------------------------------------

--
-- Stand-in structure for view `vw_program_management`
-- (See below for the actual view)
--
CREATE TABLE `vw_program_management` (
`id` int(11)
,`programCode` varchar(10)
,`programName` varchar(100)
,`departmentCode` varchar(10)
,`departmentName` varchar(100)
,`degreeLevel` enum('UNDERGRADUATE','GRADUATE','DOCTORAL')
,`creditRequirement` int(11)
,`isActive` tinyint(1)
,`dateCreated` datetime
,`enrolledStudents` bigint(21)
);

-- --------------------------------------------------------

--
-- Structure for view `active_terms`
--
DROP TABLE IF EXISTS `active_terms`;

CREATE ALGORITHM=UNDEFINED DEFINER=`root`@`localhost` SQL SECURITY DEFINER VIEW `active_terms`  AS SELECT `academic_term`.`termCode` AS `termCode`, concat(`academic_term`.`termCode`,' - ',`academic_term`.`termName`) AS `termDisplay` FROM `academic_term` WHERE `academic_term`.`isActive` = 1 ORDER BY `academic_term`.`startDate` DESC ;

-- --------------------------------------------------------

--
-- Structure for view `course_roster_details`
--
DROP TABLE IF EXISTS `course_roster_details`;

CREATE ALGORITHM=UNDEFINED DEFINER=`root`@`localhost` SQL SECURITY DEFINER VIEW `course_roster_details`  AS SELECT `e`.`id` AS `enrollmentID`, `e`.`courseOfferingID` AS `courseOfferingID`, `e`.`studentID` AS `studentID`, `u`.`firstName` AS `firstName`, `u`.`lastName` AS `lastName`, `u`.`email` AS `email`, `s`.`programCode` AS `programCode`, `es`.`statusName` AS `enrollmentStatus`, `e`.`enrollmentDate` AS `enrollmentDate`, `co`.`termCode` AS `termCode`, `co`.`facultyID` AS `facultyID` FROM ((((`enrollment` `e` join `student` `s` on(`e`.`studentID` = `s`.`studentID`)) join `user` `u` on(`s`.`userID` = `u`.`userID`)) join `enrollment_status` `es` on(`e`.`statusID` = `es`.`id`)) join `course_offering` `co` on(`e`.`courseOfferingID` = `co`.`id`)) ORDER BY `u`.`lastName` ASC, `u`.`firstName` ASC ;

-- --------------------------------------------------------

--
-- Structure for view `faculty_course_offerings`
--
DROP TABLE IF EXISTS `faculty_course_offerings`;

CREATE ALGORITHM=UNDEFINED DEFINER=`root`@`localhost` SQL SECURITY DEFINER VIEW `faculty_course_offerings`  AS SELECT `co`.`id` AS `courseOfferingID`, `co`.`termCode` AS `termCode`, `co`.`courseCode` AS `courseCode`, `co`.`section` AS `section`, `c`.`courseName` AS `courseName`, concat(`c`.`courseCode`,' - ',`c`.`courseName`,' (Section ',`co`.`section`,')') AS `courseDisplay`, `co`.`facultyID` AS `facultyID`, `co`.`enrolledCount` AS `enrolledCount`, `co`.`capacity` AS `capacity`, `co`.`status` AS `status` FROM (`course_offering` `co` join `course` `c` on(`co`.`courseCode` = `c`.`courseCode`)) ;

-- --------------------------------------------------------

--
-- Structure for view `student_grades`
--
DROP TABLE IF EXISTS `student_grades`;

CREATE ALGORITHM=UNDEFINED DEFINER=`root`@`localhost` SQL SECURITY DEFINER VIEW `student_grades`  AS SELECT `e`.`studentID` AS `studentID`, `co`.`termCode` AS `termCode`, `c`.`courseCode` AS `courseCode`, `c`.`courseName` AS `courseName`, `c`.`credits` AS `credits`, `g`.`grade` AS `grade`, `gs`.`gradePoint` AS `gradePoint`, `g`.`submissionDate` AS `submissionDate` FROM ((((`enrollment` `e` join `course_offering` `co` on(`e`.`courseOfferingID` = `co`.`id`)) join `course` `c` on(`co`.`courseCode` = `c`.`courseCode`)) left join `grade` `g` on(`e`.`id` = `g`.`enrollmentID`)) left join `grade_scale` `gs` on(`g`.`grade` = `gs`.`grade`)) WHERE `e`.`statusID` in (1,3) ;

-- --------------------------------------------------------

--
-- Structure for view `vw_active_departments`
--
DROP TABLE IF EXISTS `vw_active_departments`;

CREATE ALGORITHM=UNDEFINED DEFINER=`root`@`localhost` SQL SECURITY DEFINER VIEW `vw_active_departments`  AS SELECT `department`.`departmentCode` AS `departmentCode`, `department`.`departmentName` AS `departmentName`, `department`.`headOfDepartmentID` AS `headOfDepartmentID` FROM `department` WHERE `department`.`isActive` = 1 ORDER BY `department`.`departmentName` ASC ;

-- --------------------------------------------------------

--
-- Structure for view `vw_program_enrollment_stats`
--
DROP TABLE IF EXISTS `vw_program_enrollment_stats`;

CREATE ALGORITHM=UNDEFINED DEFINER=`root`@`localhost` SQL SECURITY DEFINER VIEW `vw_program_enrollment_stats`  AS SELECT `p`.`programCode` AS `programCode`, `p`.`programName` AS `programName`, `p`.`departmentCode` AS `departmentCode`, `p`.`degreeLevel` AS `degreeLevel`, count(`s`.`id`) AS `totalStudents`, min(`s`.`admissionDate`) AS `earliestAdmission`, max(`s`.`admissionDate`) AS `latestAdmission` FROM (`academic_program` `p` left join `student` `s` on(`p`.`programCode` = `s`.`programCode`)) WHERE `p`.`isActive` = 1 GROUP BY `p`.`programCode`, `p`.`programName`, `p`.`departmentCode`, `p`.`degreeLevel` ;

-- --------------------------------------------------------

--
-- Structure for view `vw_program_management`
--
DROP TABLE IF EXISTS `vw_program_management`;

CREATE ALGORITHM=UNDEFINED DEFINER=`root`@`localhost` SQL SECURITY DEFINER VIEW `vw_program_management`  AS SELECT `p`.`id` AS `id`, `p`.`programCode` AS `programCode`, `p`.`programName` AS `programName`, `p`.`departmentCode` AS `departmentCode`, `d`.`departmentName` AS `departmentName`, `p`.`degreeLevel` AS `degreeLevel`, `p`.`creditRequirement` AS `creditRequirement`, `p`.`isActive` AS `isActive`, `p`.`dateCreated` AS `dateCreated`, count(`s`.`id`) AS `enrolledStudents` FROM ((`academic_program` `p` left join `department` `d` on(`p`.`departmentCode` = `d`.`departmentCode`)) left join `student` `s` on(`p`.`programCode` = `s`.`programCode`)) WHERE `p`.`isActive` = 1 GROUP BY `p`.`id`, `p`.`programCode`, `p`.`programName`, `p`.`departmentCode`, `d`.`departmentName`, `p`.`degreeLevel`, `p`.`creditRequirement`, `p`.`isActive`, `p`.`dateCreated` ;

--
-- Indexes for dumped tables
--

--
-- Indexes for table `academic_program`
--
ALTER TABLE `academic_program`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `programCode` (`programCode`),
  ADD KEY `departmentCode` (`departmentCode`);

--
-- Indexes for table `academic_term`
--
ALTER TABLE `academic_term`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `termCode` (`termCode`);

--
-- Indexes for table `course`
--
ALTER TABLE `course`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `courseCode` (`courseCode`),
  ADD KEY `idx_course_dept` (`departmentCode`);

--
-- Indexes for table `course_offering`
--
ALTER TABLE `course_offering`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `unique_course_offering` (`courseCode`,`termCode`,`section`),
  ADD KEY `idx_course_offering_term` (`termCode`),
  ADD KEY `idx_course_offering_faculty` (`facultyID`);

--
-- Indexes for table `course_schedule`
--
ALTER TABLE `course_schedule`
  ADD PRIMARY KEY (`id`),
  ADD KEY `course_offering_id` (`course_offering_id`);

--
-- Indexes for table `department`
--
ALTER TABLE `department`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `departmentCode` (`departmentCode`);

--
-- Indexes for table `enrollment`
--
ALTER TABLE `enrollment`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `unique_enrollment` (`studentID`,`courseOfferingID`),
  ADD KEY `statusID` (`statusID`),
  ADD KEY `idx_enrollment_student` (`studentID`),
  ADD KEY `idx_enrollment_course` (`courseOfferingID`),
  ADD KEY `idx_enrollment_student_term` (`studentID`,`courseOfferingID`);

--
-- Indexes for table `enrollment_status`
--
ALTER TABLE `enrollment_status`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `statusName` (`statusName`);

--
-- Indexes for table `faculty`
--
ALTER TABLE `faculty`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `userID` (`userID`),
  ADD KEY `idx_faculty_dept` (`departmentCode`);

--
-- Indexes for table `grade`
--
ALTER TABLE `grade`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `enrollmentID` (`enrollmentID`),
  ADD KEY `grade` (`grade`),
  ADD KEY `idx_grade_enrollment` (`enrollmentID`),
  ADD KEY `idx_grade_faculty` (`submittedBy`),
  ADD KEY `idx_grade_course` (`enrollmentID`);

--
-- Indexes for table `grade_scale`
--
ALTER TABLE `grade_scale`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `grade` (`grade`);

--
-- Indexes for table `student`
--
ALTER TABLE `student`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `userID` (`userID`),
  ADD UNIQUE KEY `studentID` (`studentID`),
  ADD KEY `idx_student_program` (`programCode`);

--
-- Indexes for table `user`
--
ALTER TABLE `user`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `userID` (`userID`),
  ADD UNIQUE KEY `email` (`email`),
  ADD UNIQUE KEY `username` (`username`),
  ADD KEY `idx_user_role` (`roleID`);

--
-- Indexes for table `user_role`
--
ALTER TABLE `user_role`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `roleName` (`roleName`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `academic_program`
--
ALTER TABLE `academic_program`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=23;

--
-- AUTO_INCREMENT for table `academic_term`
--
ALTER TABLE `academic_term`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=28;

--
-- AUTO_INCREMENT for table `course`
--
ALTER TABLE `course`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=21;

--
-- AUTO_INCREMENT for table `course_offering`
--
ALTER TABLE `course_offering`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=57;

--
-- AUTO_INCREMENT for table `course_schedule`
--
ALTER TABLE `course_schedule`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=93;

--
-- AUTO_INCREMENT for table `department`
--
ALTER TABLE `department`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=15;

--
-- AUTO_INCREMENT for table `enrollment`
--
ALTER TABLE `enrollment`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=91;

--
-- AUTO_INCREMENT for table `enrollment_status`
--
ALTER TABLE `enrollment_status`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=5;

--
-- AUTO_INCREMENT for table `faculty`
--
ALTER TABLE `faculty`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=14;

--
-- AUTO_INCREMENT for table `grade`
--
ALTER TABLE `grade`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=46;

--
-- AUTO_INCREMENT for table `grade_scale`
--
ALTER TABLE `grade_scale`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=61;

--
-- AUTO_INCREMENT for table `student`
--
ALTER TABLE `student`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=25;

--
-- AUTO_INCREMENT for table `user`
--
ALTER TABLE `user`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=46;

--
-- AUTO_INCREMENT for table `user_role`
--
ALTER TABLE `user_role`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=5;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
